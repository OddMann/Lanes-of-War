#ifndef KAPPAPRIDE_STATEMENU_H
#define KAPPAPRIDE_STATEMENU_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../State.h"


class stateMenu: public State {

    void GoNext(Machine &machine);
    sf::Text menuText;
    sf::Text startGameText;
    sf::Text settingsText;
    sf::Text exitText;
    sf::Font font;
    int menuChoice = -1;
    bool textSetup = false;
    float deltaTime = 0;
};


#endif //KAPPAPRIDE_STATEMENU_H
