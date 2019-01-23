//
// Created by Kringle on 19/10/2018.
//

#ifndef KAPPAPRIDE_MACHINE_H
#define KAPPAPRIDE_MACHINE_H

#include <map>
#include "../App/App.h"
#include "../StateMachine/States/stateMenu.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class State;

class Machine {
public:
    enum class StateId { SPLASH, START, MENU, SETTINGS, PAUSE, END, PLAY, HIGHSCORE, LOADGAME, EXIT, COUNT };
    Machine(App &app);
    ~Machine();

    void GoNext();
    void SetState(StateId state);
    StateId GetState() const { return state; }
    bool GetRunning() const { return running; }
    void SetRunning(bool running) { this->running = running; }
    sf::Music MenuMusic;
    sf::Music BackgroundMusic;
    sf::Music IntroSplash;
    App &app;
protected:
    bool running;
    StateId state;
    std::map<StateId, State*> states;
};



#endif //KAPPAPRIDE_MACHINE_H
