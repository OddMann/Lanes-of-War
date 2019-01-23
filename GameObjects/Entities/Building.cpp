//
// Created by Kringle on 19/10/2018.
//

#include "Building.h"
#include "../../App/App.h"
#include <cmath>
Building_t::Building_t(Json::Value &building)
{
    type_Id = building["Id"].asInt();
    name = building["name"].asString();
    hp = building["hp"].asInt();
    def = building["def"].asInt();
    atk = building["atk"].asInt();
    width = building["width"].asInt();
    height = building["height"].asInt();
    cost = building["cost"].asInt();
    income = building["income"].asFloat();
    attackTime =building["attackTime"].asInt();
    attacks = building["attacks"].asInt();
    range = building["range"].asInt();
    for (Json::Value::ArrayIndex i = 0; i != building["upgrades"].size(); i++)
        upgrades.push_back(building["upgrades"][i].asInt());
    for (Json::Value::ArrayIndex i = 0; i != building["abilities"].size(); i++)
        abilities.push_back(building["abilities"][i].asInt());
    for (Json::Value::ArrayIndex i = 0; i != building["units"].size(); i++)
        units.push_back(building["units"][i].asInt());

    sf::Uint8 r, g, b = 0;
    r = (sf::Uint8)building["color"][0].asInt();
    g = (sf::Uint8)building["color"][1].asInt();
    b = (sf::Uint8)building["color"][2].asInt();
    color = {r,g,b};
}
void Building_t::swap(Building_t& first, Building_t& second)
{
    using std::swap;
    swap(first.type_Id, second.type_Id);
    swap(first.name, second.name);
    swap(first.hp, second.hp);
    swap(first.def, second.def);
    swap(first.atk, second.atk);
    swap(first.width, second.width);
    swap(first.height, second.height);
    swap(first.cost, second.cost);
    swap(first.income, second.income);
    swap(first.attackTime, second.attackTime);
    swap(first.attacks, second.attacks);
    swap(first.range, second.range);
    swap(first.upgrades, second.upgrades);
    swap(first.abilities, second.abilities);
    swap(first.units, second.units);
    swap(first.color, second.color);
}

Building_t& Building_t::operator=(Building_t other)
{
    swap(*this, other);
    return *this;
}
Building::Building(Building_t const &b, Node &node, Team &team, bool base, Map &map) : Entity(map,team) {

    Id = nextId++;
    Entity_Id = nextE_Id++;
    type_Id = b.type_Id;

    location = &node;
    position = location->pos();
    name = b.name;
    cost = b.cost;
    income = b.income;
    height = b.height;
    width = b.width;
    size = 20;
    sqsize = (int)size*(int)size;
    color = b.color;

    for(auto a: b.abilities)
    {
        abilities.emplace_back(Ability::Abilities[a],*this, map);
    }
    for(auto up: b.upgrades)
    {
        upgrades.push_back(up);
        sf::RectangleShape dot;
        dot.setFillColor(sf::Color::Green);
        statebuttons.emplace_back(dot);
    }

    for(auto u: b.units)
    {
        units[u] = Unit::Types[u];
        sf::RectangleShape dot;
        dot.setFillColor(sf::Color::Red);
        statebuttons.emplace_back(dot);
    }
    std::reverse(statebuttons.begin(),statebuttons.end());
    sf::Vector2f s_start = position - sf::Vector2f(width/2.f ,(float)height);
    sf::Vector2f pos_d[] = {{0,0},{0,5},{0,10},{5,0},{5,5},{5,10},{10,0},{10,5},{10,10}};
    int i = 0;
    for(auto& dot: statebuttons)
    {
        dot.setSize({4,4});
        dot.setOutlineThickness(1);
        dot.setOutlineColor(sf::Color::Black);
        dot.setPosition(s_start + pos_d[i]);
        i++;

    }

    health = b.hp;
    maxhealth = health;
    float barwith = (float)log10(2*maxhealth)*50/3;
    healthBar.setPosition(s_start - sf::Vector2f(-width/2.f,8));
    healthBar.setSize({barwith,5});
    healthBar.setOrigin(barwith/2.0f,0);
    healthBar.setFillColor(sf::Color::Red);
    healthBar.setOutlineColor(sf::Color::Black);
    healthBar.setOutlineThickness(1);

    def = b.def;
    attack = b.atk;
    attacks  = b.attacks;
    attackTimer = b.attackTime;
    attackTime = b.attackTime;
    if(abilities.empty())
        range = b.range;
    else
        range = abilities[0].Range();
    rangesq = range*range;
    targets.resize(attacks);

    state = State::IDLE;
    life = 60;
    targetable = true;
    alive = true;



    maxSpeed = 0;
    maxForce = 0;
    isBase = base;
    if(base)
        team.SetBase(*this);

    i = 0;
    for(auto u: units)
    {
        CreateButton(u.first, 38, 38, 1.0f, team.uiset[i].x, team.uiset[i].y, team.keys[i]);
        i++;
    }
    for(auto u: upgrades)
    {
        CreateButtonUpgrade(u, 38, 38, 1.0f,team.uiset[i].x, team.uiset[i].y, team.keys[i]),
        i++;
    }


}
Building::~Building()
{
    location = nullptr;
}

void Building::CreateButton(int Uid, int x_size, int y_size, float oThick, int x, int y, sf::Keyboard::Key key)
{

    auto button = new ButtonUnit({(float)x,(float)y}, key, x_size, y_size, oThick, team.GetColor(), Uid, team.getApp()->map, team, *this);
    buttons.push_back(button);
}
void Building::CreateButtonUpgrade(int Uid, int x_size, int y_size, float oThick, int x, int y, sf::Keyboard::Key key)
{

    auto button = new ButtonUpgrade({(float)x,(float)y}, key, x_size, y_size, oThick, {0,255,0}, Uid, team.getApp()->map, team, (void*)this);
    buttons.push_back(button);
}

void Building::CreateUnitTeam(int Id)
{

    Unit_t unit = Unit::Types[Id];
    if(team.Money() >= unit.cost)
    {
        //TODO: apply upgrades
        team.Money(-unit.cost);
        if(spawnQ.empty())
            spawnTimer = unit.cost;
        spawnQ.push(unit);

    }
}
void Building::Spawner()
{
    if(spawnQ.empty())
        return;
    if(spawnTimer <= 0)
    {
        team.getApp()->GetEntities().emplace_back(std::make_unique<Unit>(spawnQ.front(), *location, team, map));

        spawnQ.pop();
        if(!spawnQ.empty())
            spawnTimer = spawnQ.front().time;
    }
    else
        spawnTimer--;

}
void Building::update(std::list<std::unique_ptr<Entity>> const &entities, sf::RenderWindow &window)
{
    draw(window);
    if (!isOk())
    {
        return;
    }
    aquireTargets(entities);
    if(attackTimer <= 0)
        Attack();
    else
        targets.reset();

    buttonStates = 0;
    int i = 0;
    for(auto b: buttons)
    {
        buttonStates |= b->hover() << i;
        i++;
    }
    if(attackTimer > 0)
        attackTimer --;
    Spawner();
    team.Income(income);
}

void Building::aquireTargets(std::list<std::unique_ptr<Entity>> const &entities)
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
            if(d-rangesq-sqSize() <= u->sqSize())
            {
                targets.add(d,*u);

                if(u->TakeDmg(DoDmg()))
                    this->team.Money(u->GetCost() / 5);
            }
        }
    }
}
void Building::draw(sf::RenderWindow &window)
{
    sf::RectangleShape rectangle(sf::Vector2f(width,height));
    rectangle.setFillColor(color);
    rectangle.setOutlineColor(sf::Color::Black);
    rectangle.setOutlineThickness(1.0f);
    rectangle.setPosition(position);
    rectangle.setOrigin(width/2.0f, height);
    window.draw(rectangle);
    int i = 1;
    for(auto &dot: statebuttons)
    {
        if(buttonStates & i)
        {
            window.draw(dot);
        }
       i <<= 1;
    }
    float p = health/(float)maxhealth;
    healthBar.setScale({p,1});
    window.draw(healthBar);
}

std::map<int, Building_t> Building::Types;