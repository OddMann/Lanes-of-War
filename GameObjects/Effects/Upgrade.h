//
// Created by Kringle on 19/10/2018.
//

#ifndef KAPPAPRIDE_UPGRADE_H
#define KAPPAPRIDE_UPGRADE_H

#include "Effect.h"
#include "jsoncpp/json/json.h"
#include "UpgradeComponents/ComponentTypes.h"

class System
{
public:
    void income(void* i, void* b);
    void Health(void* a, void* e);
    void Size(void* a, void* u);
    void Attack(void* a, void* e);
    void Defence(void* a, void* e);
    void Attacks(void* a, void* e);
    void Ability(void* a, void* e);
};
typedef std::pair<int, float> component;
struct Upgrade_t
{
    Upgrade_t()
    {
        name = "temp";
        Id = 666;
        Type = 0;
    };
    Upgrade_t(Json::Value &unit);
    void swap(Upgrade_t& first, Upgrade_t& second);
    Upgrade_t& operator=(Upgrade_t other);
    std::string name;
    int Id;
    int Type;
    int cost;
    int max;
    std::vector<component> components;
};


class Upgrade: public Effect {
public:
    obj_Type Type()const override{return obj_Type::UPGRADE;}
    static std::map<int, Upgrade_t> Types;
    Upgrade(Upgrade_t &upgrade, void* t, Map &map);
    ~Upgrade();
    int Max_Rank;
    int Rank;
    int cost;
    static System system;
    void* target;
    void funct();
    std::vector<comp::component*> components;
};


#endif //KAPPAPRIDE_UPGRADE_H
