//
// Created by Kringle on 25/10/2018.
//

#ifndef KAPPAPRIDE_APP_H
#define KAPPAPRIDE_APP_H


#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../GameObjects/Object.h"

#include "../GameObjects/Spaces/Space.h"
#include "../GameObjects/Spaces/Node.h"
#include "../GameObjects/Spaces/Lane.h"

#include "../GameObjects/Interface/Button.h"
#include "../GameObjects/Interface/Buttons/ButtonUnit.h"
#include "../GameObjects/Interface/Buttons/ButtonBuild.h"
#include "../GameObjects/Interface/Buttons/ButtonUpgrade.h"
#include "../GameObjects/Interface/Buttons/ButtonTexture.h"
#include "../GameObjects/Interface/Text.h"
#include "../GameObjects/Mouse.h"

#include "../GameObjects/Entities/Entity.h"
#include "../GameObjects/Entities/Unit.h"
#include "../GameObjects/Entities/Building.h"
#include "../GameObjects/Entities/Spell.h"

#include "../GameObjects/Effects/Effect.h"
#include "../GameObjects/Effects/Ability.h"

#include "../Map/Map.h"
#include "../Layer/Layer.h"
#include "../Sprite/Sprite.h"

#include <list>
#include <vector>
#include <map>
#include <fstream>
#include <math.h>
#include <string>
#include <random>
#include <iostream>
#include <algorithm>
#include "Thor/Vectors.hpp"
#include <algorithm>
#include "../Pathing/Pathfinder.h"
#include <queue>

class Object;
class App {
public:
    friend class Team;
    friend class pf;
    friend class AI;
    std::vector<std::vector<sf::Keyboard::Key>> keysets=
            {
                    {sf::Keyboard::Q,sf::Keyboard::A,sf::Keyboard::Z,
                            sf::Keyboard::W,sf::Keyboard::S,sf::Keyboard::X,
                            sf::Keyboard::E,sf::Keyboard::D,sf::Keyboard::C},

                    {sf::Keyboard::Unknown,sf::Keyboard::Unknown,sf::Keyboard::Unknown,
                            sf::Keyboard::Unknown,sf::Keyboard::Unknown,sf::Keyboard::Unknown,
                            sf::Keyboard::Unknown,sf::Keyboard::Unknown,sf::Keyboard::Unknown}

            };

    App();
    //window
    sf::RenderWindow window;
    //clock
    sf::Clock clock;

    //sound
    sf::SoundBuffer buffer;
    sf::Sound sound;
    sf::SoundBuffer entity_buffer;

    //Getters
    std::vector<Node*>GetNodes()const{ return Nodes;}
    std::list<std::unique_ptr<Entity>>& GetEntities(){ return Entities;}
    std::vector<Team*> GetTeams()const{ return Teams;}
    std::vector<Button*> GetButtons()const{ return Buttons;}
    std::list<Interface*> GetInterfaces()const{ return Interfaces;}
    Map getMap()const{ return map;}
    Space* GetSpace(int id){ return Spaces[id];}
    int  GetUnitCount()const{return unitCount;}
    int GetLoser()const{ return loser;}


    //Game initialization
    void ImportUnit();
    void ImportBuilding();
    void ImportAbility();
    void ImportUpgrade();
    void CreateNode(Json::Value& val);
    void CreateLane(Json::Value& val);
    void CreateTeam();
    void makeMap();
    void deleteInstance();

    //Button create
    void CreateButton(sf::Vector2f pos, int x_size, int y_size, sf::Color color, std::string texture);

    //Tiled
    void mapTick(sf::RenderWindow& window, std::list<std::shared_ptr<Object>>& mapObjects, float deltaTime);
    std::list<std::shared_ptr<Object>> mapObjects;
    void mapCopyObjects();
    Map map;

    bool togglefps = false;
    bool toggleMute = false;
    bool gameRun;
    sf::Texture screenshot;



protected:
    std::list<Object*>  Objects;
    std::vector<Space*> Spaces;
    std::vector<Node*>  Nodes;
    std::list<std::unique_ptr<Entity>> Entities;
    std::vector<Button*> Buttons;
    std::list<Interface*> Interfaces;
    std::vector<int>   spawns;
    std::vector<Team*>  Teams;
    pth::PathIds pathid;
    Nowhere* nowhere;
    int loser = -1;
    int unitCount;
    void Routing();

    std::map<int,std::map<int, pth::Path>> paths;
    std::vector<pth::pathVertex> vertices;

};

class Team {
public:
    //Constructor
    Team(int money, int income, int spawn, App& app);
    //IO-sets
    std::vector<sf::Keyboard::Key> keys;
    std::vector<sf::Vector2i> uiset;
    //Getters
    int GetId()const{return Id;}
    App* getApp()const{ return &app;}
    float Money()const { return money; }
    Node* GetSpawn()const{return spawn;}
    Node* Selectt()const{return selected;}
    Mouse& GetMouse()const{return *mouse;}
    sf::Color GetColor()const{return teamColor;}
    pth::Path& getPath(int s,int d) const { return app.paths[s][d];}

    //Setters
    void Select(Node &n) {selected = &n; }
    static void ResetId(){next_Id = 0;}
    void Income(float i) { income += i; }
    void Money(float i) { money += i; }
    void SetBase(Building& b){base = &b;}

    //functions
    void CreateButton(Building_p b_p, int x_size, int y_size, float oThick, sf::Color color, int x, int y, sf::Keyboard::Key key);
    virtual bool tick();
    bool inSpace();
    void Select();
    void Selected();
    void CreateBuildingTeam(int Id, Node* node, bool base);

    //comparators
    bool operator==(int id)const{return (id == this->Id);}
    bool operator==(Team &t)const{return (t.Id == this->Id);}
    bool operator!=(Team &t)const{return (t.Id != this->Id);}

protected:
    App& app;
    int Id;
    static int next_Id;
    Space* target;
    Node* selected;
    float money;
    int baseIncome;
    float income;
    Node* spawn;
    Mouse* mouse;
    Text textMoney;
    Text textIncome;
    std::vector<Button*> buttons;
    sf::Color teamColor;
    Building* base;
    std::map<int, int> buildCount;
    std::vector<sf::Color> colors = {sf::Color::Blue, sf::Color::Red, sf::Color::Green, sf::Color::Yellow};



};
#endif //KAPPAPRIDE_APP_H
