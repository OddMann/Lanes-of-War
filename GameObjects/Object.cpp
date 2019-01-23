//
// Created by Kringle on 19/10/2018.
//

#include "Object.h"
void Object::update()
{
    position += velocity;
}
Object::Object(Map& map) : map(map)
{
    Id = nextId++;
    position = {0,0};
    velocity = {0,0};
    speed = 0;
    radius = 0;
}
Object::Object(sf::Vector2f pos, Map& map) : map(map)
{
    Id = nextId++;
    position = pos;
    velocity = {0,0};
    speed = 0;
    radius = 0;
}



int Object::nextId = 0;
