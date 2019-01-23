//
// Created by Kringle on 19/10/2018.
//

#ifndef KAPPAPRIDE_ABILITY_H
#define KAPPAPRIDE_ABILITY_H

#include "Effect.h"
#include "../Entities/Entity.h"
#include "../Entities/Spell.h"
#include "jsoncpp/json/json.h"
struct Ability;
struct Ability_t
{
    Ability_t()
    {
        name = "temp";
        Id = 666;
        atk = 0;
        hp = 0;
    };
    Ability_t(Json::Value &unit);
    void swap(Ability_t& first, Ability_t& second);
    Ability_t& operator=(Ability_t other);
    std::string name;
    sf::Vector2f origin;
    sf::Vector2f target;
    int Id;
    Spell::TYPE Type;
    int atk;
    int attacks;
    int hp;
    int size;
    int life;
    int speed;
    int range;
    bool targetable;
    std::vector<int> abilities;
};


class Ability: public Effect {
public:
    virtual obj_Type Type()const{return obj_Type::ABILITY;}
    Ability(Ability_t &ability, Entity &caster, Map& map);

    virtual void funct(sf::Vector2f pos);
    static std::map<int, Ability_t> Abilities;
    int Range()const{return range;}
private:
    Entity* caster;
    Ability_t params;
    Spell::TYPE type;
    int range;
    int size;
};


#endif //KAPPAPRIDE_ABILITY_H
