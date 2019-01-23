//
// Created by Kringle on 22/11/2018.
//

#ifndef KAPPAPRIDE_SPELL_H
#define KAPPAPRIDE_SPELL_H

#include "Entity.h"

struct Ability_t;
struct Ability;
struct Spell_t
{

};
class Spell : public Entity{
public:
    enum TYPE{AOE, SPLASH, CHAIN, PROJECT, COUNT};  //Only AOE and Projectile functions propperly
    Spell(Team &team, Map& map);
    Spell(Ability_t &params, Team &team, Map& map);
    ~Spell() override = default;
    void draw(sf::RenderWindow & window) override;
    void update(std::list<std::unique_ptr<Entity>> const &entities, sf::RenderWindow &window) override;
    void Attack(std::list<std::unique_ptr<Entity>> const &entities);
    sf::Vector2f Seek(sf::Vector2f targ);

protected:
    sf::Vector2f target;
    TYPE type;
};


#endif //KAPPAPRIDE_SPELL_H
