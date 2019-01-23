//
// Created by Kringle on 19/10/2018.
//

#ifndef KAPPAPRIDE_OBJECT_H
#define KAPPAPRIDE_OBJECT_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <memory>
#include "../Map/Map.h"
#include "Thor/Vectors.hpp"
#include "../Pathing/PathData.h"

namespace sf
{
    class RenderWindow;
    class Texture;
}

class Object {
public:
    enum class obj_Type { OBJECT, SPACE, NODE, LANE, BUTTON, ENTITY, UNIT, BUILDING, EFFECT, ABILITY, UPGRADE, COUNT };

    explicit Object(Map& map);
    explicit Object(sf::Vector2f pos, Map& map);
    virtual ~Object() = default;

    virtual obj_Type Type()const{return obj_Type::OBJECT;}

    virtual void process(float deltaTime) {}
    virtual void draw(sf::RenderWindow &window) {} //TODO Difference from example
    virtual void update();

    float X_pos()const{ return position.x;}
    float Y_pos()const{ return position.y;}
    sf::Vector2f pos()const {return position;}
    sf::Vector2f vel()const {return velocity;}
    void Pos(sf::Vector2f pos){position.x = pos.x; position.y = pos.y;}
    static void ResetId(){nextId = 0;}
    friend void oswap(Object& first, Object& second)
    {
        using std::swap;
        swap(first.name, second.name);
        swap(first.Id, second.Id);
        swap(first.position, second.position);
        swap(first.velocity, second.velocity);
        swap(first.speed, second.speed);
    }
    Object& operator=(Object other)
    {
        oswap(*this, other);
        return *this;
    }
protected:
    std::string name;
    int Id;
    static int nextId;
    sf::Vector2f position;
    sf::Vector2f velocity;
    float speed;
    Map& map;
    int radius;
};



#endif //KAPPAPRIDE_OBJECT_H
