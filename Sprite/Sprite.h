//
// Created by OddMann on 02.11.2018.
//

#ifndef KAPPAPRIDE_SPRITE_H
#define KAPPAPRIDE_SPRITE_H

#include <SFML/System/Clock.hpp>

#include "../GameObjects/Object.h"

class Sprite : public Object
{

    friend class Map;

public:
    explicit Sprite(Map& map) : Object(map) {}

    void process(float time) override;
    void draw(sf::RenderWindow& window) override;

protected:

    int id = 0;

    unsigned int gid = 0;

    float x = 0;
    float y = 0;

    float width = 0;
    float height = 0;

    int frame = 0;

    sf::Clock clock;
};


#endif //KAPPAPRIDE_SPRITE_H
