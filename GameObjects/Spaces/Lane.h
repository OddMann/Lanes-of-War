//
// Created by Kringle on 19/10/2018.
//

#ifndef KAPPAPRIDE_LANE_H
#define KAPPAPRIDE_LANE_H

#include "Space.h"
#include "map"
class Node;
class Lane: public Space {
public:
    Lane(sf::Vector2f pos, float width, Map map);
    ~Lane() = default;
    virtual obj_Type Type()const{return obj_Type::LANE;}
    void draw(sf::RenderWindow &window);

private:
};


#endif //KAPPAPRIDE_LANE_H
