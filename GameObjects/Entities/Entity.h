//
// Created by Kringle on 19/10/2018.
//

#ifndef KAPPAPRIDE_ENTITY_H
#define KAPPAPRIDE_ENTITY_H
#include "../Object.h"
#include "../../Pathing/Heap.h"
#include <list>
struct Ability_t;
struct Ability;
class System;

class closeTarget;
class Team;
class Entity: public Object {
public:
    friend class System;
    Entity(Map& map, Team& team);
    ~Entity()override = default;
    enum class State {MOVE, IDLE, CHARGE, ATTACK, DEAD, COUNT};
    obj_Type Type()const override{return obj_Type::ENTITY;}
    virtual void update(std::list<std::unique_ptr<Entity>> const &entities, sf::RenderWindow &window){}
    int getEId()const{return Entity_Id;}
    bool Alive()const{return alive;}
    class Team& GetTeam()const{return team;}
    int GetCost()const{return cost;}
    int Size()const{return size;}
    int sqSize()const{return sqsize;}
    void CastSpell(Ability_t &params);

    void Alive(bool a){alive = a;}
    bool TakeDmg(int Dmg);
    int  DoDmg();
    void Attack();
    bool isOk();
    static void ResetId(){nextE_Id = 0;}
    bool isTargetable()const{return targetable;}
    bool operator==(Entity& other){return Entity_Id == other.getEId();}
    bool operator==(Entity& other)const{return Entity_Id == other.getEId();}
    bool operator==(const Entity& other){return Entity_Id == other.getEId();}
    bool operator==(const Entity& other)const{return Entity_Id == other.getEId();}

    State GetState()const{return state;}

protected:
    State state;
    int Entity_Id;
    static int nextE_Id;
    class Team& team;
    int health;
    int maxhealth;
    int def;
    int attack;
    float size;
    int sqsize;
    //std::list<upgrades> upgrades;
    int cost;
    int attackTimer;
    int attackTime;
    int attacks;
    std::vector<Ability> abilities;
    int range;
    int rangesq;
    bool attacked;
    bool alive;
    bool targetable;
    int life;

    maxHeap targets;

    float maxSpeed;    //Max maxSpeed
    float maxForce;    //Max force
    sf::Vector2f acceleration;
    sf::Sound sound;
};


#endif //KAPPAPRIDE_ENTITY_H
