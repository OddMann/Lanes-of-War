//
// Created by Kringle on 19/10/2018.
//

#include "Unit.h"
#include "../../App/App.h"

Unit_t::Unit_t(Json::Value &unit)
{
    type_Id = unit["Id"].asInt();
    name = unit["name"].asString();
    hp = unit["hp"].asInt();
    def = unit["def"].asInt();
    atk = unit["atk"].asInt();
    size = unit["size"].asInt();
    cost = unit["cost"].asInt();
    time = unit["time"].asInt();
    speed = unit["maxSpeed"].asFloat();
    attacks = unit["attacks"].asInt();
    attackTime =unit["attackTime"].asInt();
    range = unit["range"].asInt();
    for (Json::Value::ArrayIndex i = 0; i != unit["upgrades"].size(); i++)
        upgrades.push_back(unit["upgrades"][i].asInt());
    for (Json::Value::ArrayIndex i = 0; i != unit["abilities"].size(); i++)
        abilities.push_back(unit["abilities"][i].asInt());
}
void Unit_t::swap(Unit_t& first, Unit_t& second)
{
    using std::swap;
    swap(first.type_Id, second.type_Id);
    swap(first.name, second.name);
    swap(first.hp, second.hp);
    swap(first.def, second.def);
    swap(first.atk, second.atk);
    swap(first.size, second.size);
    swap(first.cost, second.cost);
    swap(first.time, second.time);
    swap(first.speed, second.speed);
    swap(first.attacks, second.attacks);
    swap(first.range, second.range);
    swap(first.attackTime, second.attackTime);
    swap(first.upgrades, second.upgrades);
    swap(first.abilities, second.abilities);
}

Unit_t& Unit_t::operator=(Unit_t other)
{
    swap(*this, other);
    return *this;
}
Unit::Unit(Unit_t &unit, Node &space, Team &team, Map& map) : Entity(map,team)
{
    Id = nextId++;
    Entity_Id = nextE_Id++;
    name = unit.name;

    this->space = &space;
    this->Destination = &space;
    this->path = nullptr;


    cost = unit.cost;
    size = unit.size;
    sqsize = size*size;

    for(auto a: unit.abilities)
    {
        abilities.emplace_back(Ability::Abilities[a],*this, map);
    }

    health = unit.hp;
    def = unit.def;
    attack = unit.atk;
    attacks = unit.attacks;
    attackTimer = unit.attackTime;
    attackTime = unit.attackTime;
    if(abilities.empty())
        range = unit.range;
    else
        range = abilities[0].Range();
    rangesq = range*range;
    los = 60;
    losq = los*los;
    l_d = losq;
    targets.resize(attacks);

    state = State::IDLE;
    life = 60;
    targetable = true;
    alive = true;
    charge = nullptr;

    maxSpeed = unit.speed;
    speed = 0;
    maxForce = 0.1f;



    Target(space.pos());
    Pos(space.pos());

    pathProg = 1;
    prevpath = 0;


}

Unit::~Unit()
{
    space = nullptr;
    Destination = nullptr;
}

void Unit::draw(sf::RenderWindow &window)
{
    sf::CircleShape circle(size);
    circle.setFillColor(team.GetColor());
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(1.0f);
    circle.setPosition(position);
    circle.setOrigin(sf::Vector2f(size,size));
    window.draw(circle);
}


//Move function, better name would be update, as it at the moment handles more than just movement
void Unit::update(std::list<std::unique_ptr<Entity>> const &entities, sf::RenderWindow &window)
{
    //Check state
    draw(window);
    if(Destination->SId() == 0)
        return;
    if(!isOk())
    {
        return;
    }
    if(!targetable)
    {
        velocity = {0,0};
        return;
    }
    //Logic for movement update
    attacked = false;

    //Movement calculation
    if(attackTimer == 0)
    {
        switch(state)
        {
            case State::MOVE:
                acceleration += Path();
            case State::CHARGE:
            case State::ATTACK:
            case State::IDLE:
                acceleration += Seek();
                acceleration += flocking(entities);
            default:
                break;
        }
        velocity += acceleration;
    }
    else
        velocity -= velocity/2.0f;

    if(attackTimer > 0)
        attackTimer --;
    speed = thor::length(velocity);
    if(speed > maxSpeed)
    {
        velocity *= maxSpeed / speed;
        speed = maxSpeed;
    }
    acceleration = {0,0};
    position += velocity;

    updateState();
    Attack();
    nextPath();
    //State updating


}

sf::Vector2f Unit::Seek()
{
    //Function to seek a target point
    sf::Vector2f desired = target - position;
    float d;
    float limit = 0.1f;
    float cosAngle;


    if(desired.x*desired.x > 0.01f || desired.y*desired.y > 0.01f)
        d = thor::length(desired);
    else
        return {0,0};
    if(speed == 0)
    {
        cosAngle = 2;
    }
    else{

        cosAngle = thor::dotProduct(velocity, desired)/(speed*d);
        cosAngle *= -1;
        cosAngle += 1;
        cosAngle *= 1.5+limit/2+limit;
        cosAngle += 1.5;
    }

    desired *= cosAngle / d;
    return desired;
}
sf::Vector2f Unit::Seek(sf::Vector2f targ)
{
    //Function to seek a target point
    sf::Vector2f desired = targ - position;
    float d;
    float limit = 0.1f;
    float cosAngle;

    if(desired.x*desired.x > 0.01f || desired.y*desired.y > 0.01f)
        d = thor::length(desired);
    else
        return {0,0};
    if(speed == 0)
    {
        cosAngle = 2;
    }
    else{

        cosAngle = thor::dotProduct(velocity, desired)/(speed*d);
        cosAngle *= -1;
        cosAngle += 1;
        cosAngle *= 1.5+limit/2+limit;
        cosAngle += 1.5;
    }

    desired *= cosAngle / d;
    return desired;
}


sf::Vector2f Unit::Path()
{
    sf::Vector2f predict = vel();
    if(predict.x*predict.x > 0.001f || predict.y*predict.y > 0.001f)
        predict = predict / speed;
    else predict = {0,0};

    predict *= 5.0f;

    sf::Vector2f predictLoc = pos() + predict;

    sf::Vector2f a = predictLoc - nextpath.pos;
    sf::Vector2f b = nextpath.endLine->norm;
    b *= thor::dotProduct(a,b);
    sf::Vector2f normalPoint = nextpath.pos + b;
    float distanceSq = thor::squaredLength(predictLoc - normalPoint);


    if(distanceSq > pow(nextpath.width,2))
    {
        return Seek(normalPoint);
    }

    return {0,0};

}
sf::Vector2f Unit::flocking(std::list<std::unique_ptr<Entity>> const &entities)
{
    float d;
    int sepCount , aliCount, atkCount, cohCount ;
    sepCount = aliCount = atkCount = cohCount = 0;
    sf::Vector2f sum, sepSum, aliSum, atkSum, cohSum;
    sum = sepSum = aliSum = atkSum = cohSum = {0,0};


    l_d = losq;
    charge = nullptr;
    for(auto &u : entities)
    {
        //Check if current entity is itself
        if(this == u.get() || !u->isTargetable())
            continue;

        //finding distance to entity
        sf::Vector2f diff = position - u->pos();
        if(diff.x*diff.x > 0.0001f || diff.y*diff.y > 0.0001f)
            d = thor::squaredLength(diff);
        else d = 0;

        //calculate response to entity
        switch(state)
        {
            case State::MOVE:
            case State::IDLE:
                aliSum += Align(*u, d, aliCount);
            case State::CHARGE:
                cohSum += Cohesion(*u, d, cohCount);
            case State::ATTACK:
                sepSum += Seperate(*u, d, sepCount);
                aquireTargets(*u, d, atkCount);
            default:
                break;
        }
    }

    //divide each response by number to entities to respond to
    // and add the sum of all the different responses
    if(sepCount)
        sum += Sum(sepSum, 40.f, 1);
    if(aliCount)
        sum += Sum(aliSum, .5f, aliCount);
    if(cohCount)
        sum += Sum(cohSum, 1.f, cohCount);

    return sum;
}

void Unit::updateState()
{
    if(!targets.empty())
        state = State::ATTACK;
    else if(charge != nullptr)
    {
        state = State::CHARGE;
        target = charge->pos();
    }
    else if(space == Destination)
    {
        if(state != State::IDLE)
        {
            target = space->pos();
            state = State::IDLE;
        }
        newDest();
    }
    else
    {
        target = nextpath.pos;
        state = State::MOVE;
    }


}
void Unit::nextPath()
{
    if(state == State::MOVE)
    {
        sf::Vector2f a = position - nextpath.pos;
        sf::Vector2f b = nextpath.endLine->perp;
        b *= thor::dotProduct(a,b);
        sf::Vector2f normalPoint = nextpath.pos + b;
        float distanceSq = thor::squaredLength(position - normalPoint);

        if(distanceSq <  25)
        {

            //TODO: Next space/path
            if(path->nextPath(pathProg, prevpath, nextpath))
            {
                target = nextpath.pos;
            }
            else
            {
                space = Destination;
                //velocity = {0,0};
                pathProg = 0;
            }
        }

    }
}
void Unit::newDest()
{
    if(space == Destination && space->Target(team.GetId()) != nullptr)
    {
        Destination = space->Target(team.GetId());
        path = &team.getPath(space->SId(),Destination->SId());
        nextpath = path->start(space->NodeVertex().Id);
        Target(nextpath.pos);
    }
}
bool Unit::aquireTargets(Entity &e, float d, int &count)
{

    if(e.GetTeam() != team)
    {
        if(d-rangesq-sqSize() <= e.sqSize())
        {
            targets.add(d,e);
        }
        else if(d <= losq)
        {
            if(d < l_d)
            {
                charge = &e;
                l_d = d;
            }
        }
    }
    return false;
}
sf::Vector2f Unit::Align(Entity &e, float d, int &count)
{
    float losq = los*los/2.0f;
    sf::Vector2f sum = {0,0};
    if(this->team != e.GetTeam() )
        return sum;
    if(d <= losq)
    {
        sum = (e.vel());
        count ++;
    }

    return sum;
}
sf::Vector2f Unit::Seperate(Entity &e, float d, int &count)
{
    float losq = sqsize+25;
    sf::Vector2f sum = {0,0};
    if(d <= losq && e.GetTeam() == team)
    {
        sum = position - e.pos();
        if (sum.x*sum.x > 0.001f || sum.y*sum.y > 0.001f)
            sum = thor::unitVector(sum);
        else sum = {0,0};
        sum.x /= d;
        sum.y /= d;
        sum *= 160.0f;
        count ++;
    }
    return sum;
}
sf::Vector2f Unit::Cohesion(Entity &e, float d, int &count)
{
    float losq = sqsize + 100;
    sf::Vector2f sum = {0,0};
    if(d <= losq && e.GetTeam() == team)
    {
        sum = e.pos();
        count++;
    }
    return sum;
}

sf::Vector2f Unit::Sum(sf::Vector2f sum, float limit, int count)
{

    sum.x /= count;
    sum.y /= count;
    limit *= limit;

    float length;

    if (sum.x*sum.x > 0.001f || sum.y*sum.y > 0.001f)
        length = thor::squaredLength(sum);
    else return {0,0};

    if(length >= limit)
        sum *= limit / length;
    return sum;
}


std::map<int, Unit_t> Unit::Types;