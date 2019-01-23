//
// Created by OddMann on 16.12.2018.
//

#ifndef KAPPAPRIDE_STATEGAMEEND_H
#define KAPPAPRIDE_STATEGAMEEND_H

#include <SFML/Graphics.hpp>
#include "../State.h"

class stateGameEnd: public State {
    void GoNext(Machine &machine);

    int menuChoice = -1;
    sf::Font font;
    sf::Text startGameText;
    sf::Text menuText;
    sf::Text topText;
    float deltaTime = 0;
};


#endif //KAPPAPRIDE_STATEGAMEEND_H
