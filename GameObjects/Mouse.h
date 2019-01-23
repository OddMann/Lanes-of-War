//
// Created by Kringla on 18.11.2018.
//

#ifndef KAPPAPRIDE_MOUSE_H
#define KAPPAPRIDE_MOUSE_H

#include "Object.h"

class Mouse : public Object{
public:
    explicit Mouse(sf::RenderWindow &window, Map& map) : Object(map)
    {
        speed = 0;
        velocity = {0,0};
        name = "mouse";
        updatepos(window);
    }
    void draw(sf::RenderWindow &window)override
    {
        updatepos(window);
    }
private:

    void updatepos(sf::RenderWindow &window);
};
#endif //KAPPAPRIDE_MOUSE_H
