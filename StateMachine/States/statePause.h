//
// Created by Kristian on 14.12.2018.
//

#ifndef KAPPAPRIDE_STATEPAUSE_H
#define KAPPAPRIDE_STATEPAUSE_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../State.h"
#include "../Machine.h"
#include "../../App/App.h"
#include "../../GameObjects/Object.h"
#include "../../Layer/Layer.h"
#include "../../Sprite/Sprite.h"
#include "stateMenu.h"
#include "stateStart.h"
#include "stateSettings.h"

class statePause: public State {

public:
    void GoNext(Machine &machine);

private:
    sf::Font font;
    sf::Text exitText;
    sf::Text pauseText;
    sf::Text menuText;

    bool textSetup = false;
    float deltaTime = 0;
};


#endif //KAPPAPRIDE_STATEPAUSE_H
