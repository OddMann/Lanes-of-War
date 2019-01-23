//
// Created by Kringle on 19/10/2018.
//

#ifndef KAPPAPRIDE_LOT_H
#define KAPPAPRIDE_LOT_H

#include "Space.h"
#include "Lane.h"
//#include "../Entities/Building.h"
#include <map>

class Lane;
class Team;
class Building;

class Node: public Space {
public:
    Node(sf::Vector2f pos, int size, Map map);
    ~Node() = default;
    virtual obj_Type Type()const{return obj_Type::NODE;}
    bool contains(sf::Vector2f object);
    void draw(sf::RenderWindow &window)override;
    void Upadate(sf::RenderWindow &window);
    void Target(int t, Node *n){target[t] = n;}
    Node* Target(int t)const{return target[t];}
    int Radius()const{return radius;}
    std::vector<Node*> Neighbours()const{return neighbours;}
    void Neighbours(Node* n){neighbours.push_back(n);}
    pth::pathVertex &NodeVertex()const{return *nodeVertex;}
    void NodeVertex(pth::pathVertex &nV)
    {
        nodeVertex = &nV;
    }
    bool operator==(const Node &other)
    {
        return this->SId() == other.SId();
    }
    bool buildable[2];
    int owner;
    Building* b;
protected:
    Node* target[2];
    pth::pathVertex* nodeVertex;
    std::vector<Node*> neighbours;
};


#endif //KAPPAPRIDE_LOT_H
