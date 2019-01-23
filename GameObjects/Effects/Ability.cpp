//
// Created by Kringle on 19/10/2018.
//

#include "Ability.h"
#include "../../App/App.h"
Ability_t::Ability_t(Json::Value &ability)
{
    Type = static_cast<Spell::TYPE>(ability["type"].asInt());
    Id = ability["Id"].asInt();
    name = ability["name"].asString();
    hp = ability["hp"].asInt();
    atk = ability["atk"].asInt();
    attacks = ability["attacks"].asInt();
    size = ability["size"].asInt();
    life = ability["life"].asInt();
    speed = ability["speed"].asInt();
    range = ability["range"].asInt();
    targetable = ability["targetable"].asBool();
    for (Json::Value::ArrayIndex i = 0; i != ability["abilities"].size(); i++)
        abilities.push_back(ability["abilities"][i].asInt());
}
void Ability_t::swap(Ability_t& first, Ability_t& second)
{
    using std::swap;
    swap(first.Type, second.Type);
    swap(first.name, second.name);
    swap(first.hp, second.hp);
    swap(first.life, second.life);
    swap(first.atk, second.atk);
    swap(first.attacks, second.attacks);
    swap(first.size, second.size);
    swap(first.speed, second.speed);
    swap(first.range, second.range);
    swap(first.targetable, second.targetable);
    swap(first.abilities, second.abilities);
    swap(first.origin, second.origin);
    swap(first.target, second.target);
}

Ability_t& Ability_t::operator=(Ability_t other)
{
    swap(*this, other);
    return *this;
}
Ability::Ability(Ability_t &ability, Entity &caster, Map& map) : Effect(map)
{
    type = ability.Type;
    this->caster = &caster;
    params = ability;
    name = ability.name;
    range = ability.range;
    size = ability.size;

}
void Ability::funct(sf::Vector2f pos)
{
    switch(type)
    {
        case Spell::AOE:
            params.target = pos;
            break;
        case Spell::CHAIN:
        case Spell::PROJECT:
            params.target = pos;
            params.origin = caster->pos();
        default:
            break;
    }
    caster->CastSpell(params);

}
std::map<int,Ability_t> Ability::Abilities;