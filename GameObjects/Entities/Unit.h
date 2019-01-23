//
// Created by Kringle on 19/10/2018.
//

#ifndef KAPPAPRIDE_UNIT_H
#define KAPPAPRIDE_UNIT_H
#include "Entity.h"
#include "../Spaces/Node.h"
#include "jsoncpp/json/json.h"
#include <vector>
#include <map>
#include "math.h"
#include <algorithm>
#include "Thor/Vectors.hpp"
#include <iostream>
#include "../Effects/Ability.h"
struct Unit_t
{
    Unit_t()
    {
        name = "temp";
        type_Id = 666;
        hp = def = atk = size = cost = time = attackTime = attacks = range = 0;
        speed = 0;
        upgrades = abilities = {};
    };
    Unit_t(Json::Value &unit);
    Unit_t& operator=(Unit_t other);
    std::string name;
    int type_Id;
    int hp;
    int def;
    int atk;
    int size;
    std::vector<int> upgrades;
    std::vector<int> abilities;
    int cost;
    int time;
    float speed;
    int attacks;
    int attackTime;
    int range;
private:
    void swap(Unit_t& first, Unit_t& second);

};
typedef std::pair<int, Unit_t> Unit_p;
class Unit: public Entity {
public:
    //Constructor
    Unit(Unit_t &unit, Node &space,Team &team, Map &map);
    ~Unit() override;
    virtual obj_Type Type()const{return obj_Type::UNIT;}

    //Unit type map
    static std::map<int, Unit_t> Types;

    //Update functions
    void draw(sf::RenderWindow &window) override;
    void update(std::list<std::unique_ptr<Entity>> const &entities, sf::RenderWindow &window) override;

    //Movement functions
    sf::Vector2f flocking(std::list<std::unique_ptr<Entity>> const &entities);
    sf::Vector2f Seek();
    sf::Vector2f Seek(sf::Vector2f targ);
    bool aquireTargets(Entity &e, float d, int &count);
    sf::Vector2f Align(Entity &e, float d, int &count);
    sf::Vector2f Seperate(Entity &e, float d, int &count);
    sf::Vector2f Cohesion(Entity &e, float d, int &count);
    sf::Vector2f Sum(sf::Vector2f sum, float limit, int count);
    sf::Vector2f Path();
    void updateState();
    void nextPath();
    void newDest();

    void Target(sf::Vector2f target)
    {
        this->target = target;
    }

protected:
    //Location
    Node* space;
    Node* Destination;
    sf::Vector2f target;
    Entity* charge;
    float l_d;

    int los;
    float losq;

    //movement
    pth::Path* path;
    pth::nextVertex nextpath;
    int prevpath;
    int pathProg;
};


#endif //KAPPAPRIDE_UNIT_H
