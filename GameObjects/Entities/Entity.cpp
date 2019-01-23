//
// Created by Kringle on 19/10/2018.
//

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Building.h"
#include "../../App/App.h"

#include <iostream>

Entity::Entity(Map& map, Team& team) : Object(map), team(team)
{
    Id = nextId++;
    Entity_Id = nextE_Id++;


}
bool Entity::TakeDmg(int Dmg)
{

    if (Dmg - def <= 0 && Dmg != 0)
        health --;
    else if(Dmg == 0)
    {}
    else
        health -= Dmg-def;
    return health <= 0;
    //std::cout << "unit" << Id << "took: " << Dmg << "dmg" << std::endl;
}

bool Entity::isOk()
{
    if(health <= 0 && targetable)
    {
        if(!team.getApp()->toggleMute)
        {
            sound.setBuffer(team.getApp()->entity_buffer);
            sound.play();
            sound.setVolume(10.f);
        }
        life = 60;
        targetable = false;
        state = State::DEAD;
        return true;
    }
    if(life <= 0 && !targetable)
    {
        Alive(false);
        return false;
    }
    else if(!targetable)
        life--;
    return true;
}
int  Entity::DoDmg() {
    //std::cout << "unit" << Entity_Id << "did: " << attack << "dmg" << std::endl;
    return attack;
}
void Entity::Attack()
{
    //Attacking
    while(!targets.empty())
    {
        auto e = targets.pop();

        for(auto a: abilities)
        {
            a.funct(e->pos());
        }

        if(e->TakeDmg(DoDmg()))
        {
            this->team.Money(e->GetCost() / 5);
        }
        attackTimer = attackTime;
    }
}

void Entity::CastSpell(Ability_t &params)
{
    team.getApp()->GetEntities().emplace_back(std::make_unique<Spell>(params, team, map));
}

int Entity::nextE_Id = 0;
