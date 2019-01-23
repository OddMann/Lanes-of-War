//
// Created by Kringla on 18.11.2018.
//

#include "Mouse.h"
#include "../App/App.h"
#include "Thor/Vectors.hpp"
void Mouse::updatepos(sf::RenderWindow &window)
{
    sf::Vector2i posI = sf::Mouse::getPosition(window);
    position = {(float)posI.x,(float)posI.y};
}