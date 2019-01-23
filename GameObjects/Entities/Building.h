//
// Created by Kringle on 19/10/2018.
//

#ifndef KAPPAPRIDE_BUILDING_H
#define KAPPAPRIDE_BUILDING_H

#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "../Spaces/Node.h"
#include "jsoncpp/json/json.h"
#include <map>
#include <queue>
#include "../Effects/Ability.h"
#include "../Effects/Upgrade.h"
class Team;
class Unit_t;
class Button;
class System;
struct Building_t
{
    Building_t()
    {
        name = "temp";
        type_Id = 666;
        hp = def = atk = height = width = cost = attackTime = attacks = 0;
        upgrades = abilities = {};
    };
    Building_t(Json::Value &building);
    Building_t& operator=(Building_t other);
    std::string name;
    int type_Id;
    int hp;
    int def;
    int atk;
    int height;
    int width;

    std::vector<int> upgrades;
    std::vector<int> abilities;
    std::vector<int> units;

    int cost;
    float income;
    int attackTime;
    int attacks;
    int range;
    sf::Color color;
private:
    void swap(Building_t& first, Building_t& second);

};


typedef std::pair<int, Building_t> Building_p;


class Building: public Entity {
public:
    friend class System;
    Building(Building_t const &b, Node &node, Team &team, bool base, Map &map);
    ~Building()override;
    obj_Type Type()const override{return obj_Type::BUILDING;}
    int Type_Id()const{return type_Id;}
    static std::map<int, Building_t> Types;

    std::map<int, Unit_t> units;

    void draw(sf::RenderWindow &window)override;
    void update(std::list<std::unique_ptr<Entity>> const &entities, sf::RenderWindow &window)override;
    void aquireTargets(std::list<std::unique_ptr<Entity>> const &entities);
    Button* GetButton(int i)
    {
        if(i >= 0 || (int)buttons.size() > i)
            return buttons[i];
        else
            return nullptr;
    }
    void CreateButton(int Uid, int x_size, int y_size, float oThick, int x, int y, sf::Keyboard::Key key);
    void CreateButtonUpgrade(int Uid, int x_size, int y_size, float oThick, int x, int y, sf::Keyboard::Key key);
    std::vector<Button*> GetButtons()const{return buttons;}
    sf::RectangleShape base;
    bool IsBase()const{return isBase;}
    void Spawner();
    bool spawnQempty(){return spawnQ.empty();}
    void CreateUnitTeam(int Id);

private:
    int type_Id;
    //int Building_Id;

    std::vector<int> upgrades;
    std::vector<Button*> buttons;
    std::vector<sf::RectangleShape> statebuttons;
    sf::RectangleShape healthBar;
    int buttonStates;

    Node* location;
    int spawnTimer;
    float income;



    std::queue<Unit_t> spawnQ;
    //int characterSize;
    float width;
    float height;
    bool isBase;
    sf::Color color;

    //std::list<effect> effects;
};


#endif //KAPPAPRIDE_BUILDING_H
