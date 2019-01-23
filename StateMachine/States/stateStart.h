//
// Created by Kringle on 19/10/2018.
//

#ifndef KAPPAPRIDE_STATESPASH_H
#define KAPPAPRIDE_STATESPASH_H

#include "../State.h"
#include <SFML/Audio.hpp>
#include "../../App/App.h"
#include "../Machine.h"
#include "../../GameObjects/Interface/Text.h"

class stateStart: public State
{
public:
    void GameInit(App &app);
    Machine::StateId GameLoop(App &app);
    void GoNext(Machine &machine);
    void fpsCounter(App &app);

    float deltaTime = 0;
    bool run = false;

protected:
    float fpscount;
    sf::Font font;
    sf::Text fps;
    sf::Time time;
    sf::Clock clock;
};


#endif //KAPPAPRIDE_STATESPASH_H
