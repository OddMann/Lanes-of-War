#ifndef KAPPAPRIDE_STATESPLASH_H
#define KAPPAPRIDE_STATESPLASH_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio/Music.hpp>

#include "../State.h"

class stateSplash: public State {

    void GoNext(Machine &machine);
    float deltaTime = 0;
    bool run = false;

    sf::Clock SplashTimer;
    float secTimer;

};


#endif