//
// Created by Kringle on 22/11/2018.
//

#include "Spell.h"
#include "../../App/App.h"
#include "../Effects/Ability.h"

Spell::Spell(Team &team, Map& map) : Entity(map,team)
{
    type = Spell::TYPE::COUNT;
    position = {0,0};
}
Spell::Spell(Ability_t &params, Team &team, Map& map) : Entity(map, team)
{

    switch(params.Type)
    {
        case AOE:
            position = params.target;
            break;
        case SPLASH:
            break;
        case CHAIN:
            target = params.target;
            position = params.origin;
            break;
        case PROJECT:
            target = params.target;
            position = params.origin;
        default:
            break;

    }
    type = params.Type;
    Id = nextId++;
    Entity_Id = nextE_Id;
    name = params.name;

    if(abilities.empty())
        range = params.range;
    else
        range = abilities[0].Range();
    rangesq = range*range;
    size = params.size;
    sqsize = size*size;
    speed = params.speed;
    attack = params.atk;
    attacks = params.attacks;
    targets.resize(attacks);

    life = params.life;
    health = params.hp;
    targetable = params.targetable;

    for(auto a: params.abilities)
    {
        abilities.emplace_back(Ability::Abilities[a],*this, map);
    }

    alive = true;
}


void Spell::draw(sf::RenderWindow & window)
{
    sf::CircleShape circle(size);
    circle.setFillColor(sf::Color::Yellow);
    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(1.0f);
    circle.setPosition(position);
    circle.setOrigin(sf::Vector2f(size,size));
    window.draw(circle);
}

void Spell::update(std::list<std::unique_ptr<Entity>> const &entities, sf::RenderWindow &window)
{
    draw(window);
    if(life <= 0)
    {
        for(auto a: abilities)
        {
            if(type == PROJECT)
                a.funct(pos());
            else if(type == AOE)
            {
                while(!targets.empty())
                {

                    sf::Vector2f t = targets.pop()->pos();
                    target = t;
                    a.funct(t);

                }

            }
        }
        Alive(false);
    }
    if(!alive)
        return;
    if(type != CHAIN)
        life--;
    acceleration = {0,0};
    switch(type)
    {
        case CHAIN:
        case PROJECT:
            acceleration += Seek(target);
            velocity += acceleration;
            if(thor::squaredLength(velocity) > 0.04f)
                thor::setLength(velocity,speed);
            else
                velocity = {0,0};
            position += velocity;
            break;
        case AOE:
            break;
        default:

            break;
    }
    Attack(entities);


}

void Spell::Attack(std::list<std::unique_ptr<Entity>> const &entities)
{

    for(auto &u : entities)
    {
        //Check if current entity is itself
        if(this == u.get() || !u->isTargetable())
            continue;

        //finding distance to entity, with a 0 guard incase they overlap
        //to prevent dividing by zero
        float d;
        sf::Vector2f diff = position - u->pos();
        d = thor::squaredLength(diff);


        if(u->GetTeam() != team)
        {
            if(d-sqSize() <= u->sqSize())
            {
                targets.add(d,*u);

                if(u->TakeDmg(DoDmg()))
                    this->team.Money(u->GetCost() / 5);
                attackTimer = attackTime;
            }
        }

    }
    if(!targets.empty())
    {
        switch(type)
        {
            case AOE:
                life = 0;
                break;
            case SPLASH:
                life = 0;
                break;
            case CHAIN:
                life--;
                break;
            case PROJECT:
                life = 0;
                break;
            case COUNT:
                break;
        }
    }
}

sf::Vector2f Spell::Seek(sf::Vector2f targ)
{
    //Function to seek a target point
    sf::Vector2f desired = targ - position;
    float d;
    float limit = 0.1f;
    float cosAngle;

    if(desired.x*desired.x > 0.01f || desired.y*desired.y > 0.01f)
        d = thor::length(desired);
    else
    {
        return {0,0};

    }

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