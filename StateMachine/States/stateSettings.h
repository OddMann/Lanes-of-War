//
// Created by Kristian on 16.11.2018.
//

#ifndef KAPPAPRIDE_STATESETTINGS_H
#define KAPPAPRIDE_STATESETTINGS_H

#include <SFML/Graphics.hpp>
#include "../State.h"
#include "../Machine.h"
#include "../../App/App.h"
#include "../../GameObjects/Object.h"
#include "../../Layer/Layer.h"
#include "../../Sprite/Sprite.h"
#include "../../GameObjects/Interface/Text.h"
#include "stateMenu.h"

class stateSettings: public State {

public:
    void GoNext(Machine &machine);

private:
    sf::Text settingsHeader;
    sf::Text toggleFPS;
    sf::Text fpsHeader;
    sf::Text muteHeader;
    sf::Text toggleMUTE;
    sf::Text back;
    sf::Font font;

    int menuChoice = -1;
    bool textSetup = false;
    float deltaTime = 0;
};


#endif //KAPPAPRIDE_STATESETTINGS_H
