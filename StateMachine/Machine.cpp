//
// Created by Kringle on 19/10/2018.
//

#include <iostream>
#include "Machine.h"
#include "State.h"
#include "States/stateStart.h"
#include "States/stateMenu.h"
#include "States/stateSplash.h"
#include "States/stateSettings.h"
#include "States/statePause.h"
#include "States/stateGameEnd.h"

Machine::Machine(App &app): app(app)
{
    app.window.create(sf::VideoMode(1280, 720), "KAPPA", sf::Style::Fullscreen);
    sf::View view = app.window.getDefaultView();
    view.setSize(view.getSize().x / 1, view.getSize().y / 1);           //If you want to make the game, not the window bigger, change 1 to something else
    view.setCenter(view.getCenter().x / 1, view.getCenter().y / 1);     //2 = Double in size, 1,5 = 50% bigger
    app.window.setView(view);                                           //Also don't forget to edit the resolution to the multiplier you made
    //app.window.setVerticalSyncEnabled(true);
    app.window.setFramerateLimit(60);
    running = true;

    state = StateId::SPLASH;


    // Add states to the state map
    states.emplace(StateId::MENU, new stateMenu());
    states.emplace(StateId::SETTINGS, new stateSettings());
    states.emplace(StateId::START, new stateStart());
    states.emplace(StateId::PAUSE, new statePause());
    states.emplace(StateId::SPLASH, new stateSplash());
    states.emplace(StateId::END, new stateGameEnd());

}

Machine::~Machine()
{
    // Free the states from memory
    for (auto state: states)
        delete state.second;

    states.clear();
}

void Machine::GoNext()
{
    states[state]->GoNext(*this);
}

void Machine::SetState(StateId state)
{
    this->state = state;
}
