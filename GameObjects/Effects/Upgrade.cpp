//
// Created by Kringle on 19/10/2018.
//

#include "Upgrade.h"
#include "../Entities/Building.h"
#include "../Entities/Unit.h"

Upgrade_t::Upgrade_t(Json::Value &upgrade)
{
    Id = upgrade["Id"].asInt();
    name = upgrade["name"].asString();
    Type = upgrade["type"].asInt();
    cost = upgrade["cost"].asInt();
    max = upgrade["max"].asInt();



    for(Json::Value& n: upgrade["components"])
    {
        component c;
        c.first =  n["tag"].asInt();
        c.second = n["str"].asFloat();
        components.push_back(c);

    }

}
void Upgrade_t::swap(Upgrade_t& first, Upgrade_t& second)
{
    using std::swap;
    swap(first.name, second.name);
    swap(first.Id, second.Id);
    swap(first.Type, second.Type);
    swap(first.cost, second.cost);
    swap(first.max, second.max);
    swap(first.components, second.components);
}

Upgrade_t& Upgrade_t::operator=(Upgrade_t other)
{
    swap(*this, other);
    return *this;
}
Upgrade::Upgrade(Upgrade_t &upgrade, void* t, Map &map) : Effect(map)
{
    target = t;
    cost = upgrade.cost;
    Max_Rank = upgrade.max;
    Rank = 0;
    for(auto c: upgrade.components)
    {
        // o: baseIncome, 1: health, 2: size, 3: attack, 4: defence, 5: attacks, 6: ability
        switch(c.first)
        {
            case 0:
                components.emplace_back(new comp::income(c.second));
                break;
            case 1:
                components.emplace_back(new comp::Health(c.second));
                break;
            case 2:
                components.emplace_back(new comp::Size(c.second));
                break;
            case 3:
                components.emplace_back(new comp::Attack(c.second));
                break;
            case 4:
                components.emplace_back(new comp::Defence(c.second));
                break;
            case 5:
                components.emplace_back(new comp::Attacks(c.second));
                break;
            case 6:
                components.emplace_back(new comp::Ability(c.second));
                break;
            default:
                std::cout << "bad component type"<< std::endl;
        }
    }
}
Upgrade::~Upgrade()
{
    for(auto c: components)
    {
        delete(c);
    }
}
void System::income(void* i, void* b)
{
    auto B = (Building*)b;
    auto I = (comp::income*)i;
    B->income += I->add;
}
void System::Health(void* i, void* e)
{
    auto E = (Entity*)e;
    auto I = (comp::Health*)i;
    E->health += (int)I->add;
}
void System::Size(void* i, void* u)
{
    auto U = (Unit*)u;
    auto I = (comp::Size*)i;
    U->size += I->add;
}
void System::Attack(void* i, void* e)
{
    auto E = (Entity*)e;
    auto I = (comp::Attack*)i;
    E->attack += (int)I->add;
}
void System::Defence(void* i, void* e)
{
    auto E = (Entity*)e;
    auto I = (comp::Defence*)i;
    E->def += (int)I->add;
}
void System::Attacks(void* i, void* e)
{
    auto E = (Entity*)e;
    auto I = (comp::Attacks*)i;
    E->attacks += (int)I->add;
    E->targets.resize(E->attacks);
}
void System::Ability(void* i, void* e)
{
    auto E = (Entity*)e;
    auto I = (comp::Ability*)i;
    E->abilities.emplace_back(Ability::Abilities[(int)I->add],*E, E->map);

    if(E->range < Ability::Abilities[(int)I->add].range)
    {
        E->range = Ability::Abilities[(int)I->add].range;
        E->rangesq = E->range*E->range;
    }
}




void Upgrade::funct()
{
    for(auto c: components)
    {
        switch(c->Id)
        {
            case 0:
                system.income((void*)c, target);
                break;
            case 1:
                system.Health((void*)c, target);
                break;
            case 2:
                system.Size((void*)c, target);
                break;
            case 3:
                system.Attack((void*)c, target);
                break;
            case 4:
                system.Defence((void*)c, target);
                break;
            case 5:
                system.Attacks((void*)c, target);
                break;
            case 6:
                system.Ability((void*)c, target);
                break;
            default:
                std::cout << "bad component Type" << std::endl;
        }
    }
    Rank++;
}
std::map<int, Upgrade_t> Upgrade::Types;
System Upgrade::system;