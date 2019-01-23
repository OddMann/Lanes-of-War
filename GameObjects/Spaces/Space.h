//
// Created by Kringle on 19/10/2018.
//

#ifndef KAPPAPRIDE_SPACE_H
#define KAPPAPRIDE_SPACE_H

#include "../Object.h"
#include <list>

class Unit;
class Entity;

class Space: public Object {
public:

    explicit Space(Map& map);
    explicit Space(sf::Vector2f pos, float width, Map& map);
    ~Space() = default;
    virtual obj_Type Type()const{return obj_Type::SPACE;}

    int SId()const{return Space_Id;}
    float Width()const{return width;}
    size_t size();

    static void ResetId(){nextS_Id = 1;}
    void Attach_Space(int space_Id, sf::Vector2f pos);
    std::map<int, sf::Vector2f>const& getNeighboors(){return attached_Spaces;}


protected:
    float width;
    int Space_Id;
    static int nextS_Id;
    std::map<int, sf::Vector2f> attached_Spaces;
    std::vector<sf::Vector2f> spaces_Vector;
    std::vector<pth::pathVertex> pathVertexes;
    int numSpaces;
};

class Nowhere: public Space{
public:
    Nowhere(Map& map) : Space(map)
    {
    }
    ~Nowhere() = default;
};

#endif //KAPPAPRIDE_SPACE_H
