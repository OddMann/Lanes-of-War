#include "stateSplash.h"
#include "../Machine.h"
#include "../../App/App.h"
#include "../../GameObjects/Object.h"
#include "../../Layer/Layer.h"
#include "../../Sprite/Sprite.h"

#include <SFML/Graphics.hpp>
#include <iostream>

void stateSplash::GoNext(Machine &machine){

    if (!run) {
        if (secTimer < 5) {
            if (!machine.IntroSplash.openFromFile("MusicAndSound/Music/IntroSplash.wav")) {
                std::cout << "Failed to load splash sound" << std::endl;
            }
            machine.IntroSplash.play();

            if (!machine.MenuMusic.openFromFile("MusicAndSound/Music/MenuMusic.wav")) {
                std::cout << "Failed to load music" << std::endl;
            }

            machine.MenuMusic.play();
            machine.MenuMusic.setLoop(true);
            machine.MenuMusic.setVolume(10.f);
        }
        run = true;
    }

        machine.app.clock.restart();

        machine.app.window.clear(sf::Color::Black);

        machine.app.mapTick(machine.app.window, machine.app.mapObjects, deltaTime);
        deltaTime = machine.app.clock.getElapsedTime().asSeconds();
        machine.app.clock.restart();

        sf::Event event;

        while (machine.app.window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    machine.app.window.close();
                    exit(0);
                default:
                    break;
            }
        }
        secTimer = SplashTimer.getElapsedTime().asSeconds();

        if (secTimer >= 5) {
            machine.app.mapObjects.clear();
            if (!machine.app.map.loadFromFile("MapData/Splash.json")) {
                std::cout << "Failed to load Splash data" << std::endl;
            }
            machine.app.mapCopyObjects();
        } else {
            if (!machine.app.map.loadFromFile("MapData/Splash2.json")) {
                std::cout << "Failed to load Splash2" << std::endl;
            }
            machine.app.mapCopyObjects();
        }

        if (secTimer >= 10 || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            machine.IntroSplash.pause();
            machine.app.mapObjects.clear();

            machine.SetState(Machine::StateId::MENU);
        }
        machine.app.window.display();
};
