#include <iostream>
#include "stateMenu.h"
#include "../Machine.h"
#include "../../App/App.h"
#include "../../GameObjects/Object.h"
#include "../../Layer/Layer.h"
#include "../../Sprite/Sprite.h"
#include "stateSettings.h"
#include <SFML/Audio.hpp>

#define STARTGAME   0
#define SETUP       1
#define EXITGAME    2
#define NONE       -1

void stateMenu::GoNext(Machine &machine)
{
    if(!machine.app.gameRun)
    {;
        if (!machine.app.map.loadFromFile("MapData/Menu.json")) {
            std::cout << "Failed to load map data" << std::endl;
        }

        machine.app.mapCopyObjects();

        machine.app.CreateButton({640 , 240}, 350, 80, sf::Color::White, "MENUBUTTON");  //Interface_Id 0
        machine.app.CreateButton({640 , 360}, 350, 80, sf::Color::White, "MENUBUTTON");  //Interface_Id 1
        machine.app.CreateButton({640 , 480}, 350, 80, sf::Color::White, "MENUBUTTON");  //Interface_Id 2

        machine.app.GetButtons()[0]->updateDraw(sf::Color::White);
        machine.app.GetButtons()[1]->updateDraw(sf::Color::White);
        machine.app.GetButtons()[2]->updateDraw(sf::Color::White);

        machine.BackgroundMusic.pause();

        if (!machine.app.toggleMute)
        {
            machine.MenuMusic.play();
            machine.MenuMusic.setLoop(true);
            machine.MenuMusic.setVolume(20.f);
        }

        machine.app.gameRun = true;
    }

    if (!font.loadFromFile("Fonts/GIL.ttf"))
        std::cerr << "Failed to load font" << std::endl;

    machine.app.clock.restart();

    machine.app.window.clear(sf::Color::White);

    machine.app.mapTick(machine.app.window, machine.app.mapObjects, deltaTime);
    deltaTime = machine.app.clock.getElapsedTime().asSeconds();
    machine.app.clock.restart();

    for (auto& b: machine.app.GetButtons())
    {
        b->draw(machine.app.window);
    }

    if(!textSetup) {
        menuText.setFont(font);
        menuText.setCharacterSize(40);
        menuText.setPosition(machine.app.window.getSize().x / 2, 150);
        menuText.setString("Lanes of War");
        menuText.setOutlineThickness(2);
        menuText.setOutlineColor(sf::Color::Black);
        menuText.setOrigin(menuText.getLocalBounds().width / 2, menuText.getLocalBounds().height / 2);

        startGameText.setFont(font);
        startGameText.setCharacterSize(40);
        startGameText.setPosition(machine.app.window.getSize().x / 2, 225);
        startGameText.setString("Start Game");
        startGameText.setOutlineThickness(1);
        startGameText.setOutlineColor(sf::Color::Black);
        startGameText.setOrigin(startGameText.getLocalBounds().width / 2, startGameText.getLocalBounds().height / 2);

        settingsText.setFont(font);
        settingsText.setCharacterSize(40);
        settingsText.setPosition(machine.app.window.getSize().x / 2, 350);
        settingsText.setString("Settings");
        settingsText.setOutlineThickness(1);
        settingsText.setOutlineColor(sf::Color::Black);
        settingsText.setOrigin(settingsText.getLocalBounds().width / 2, settingsText.getLocalBounds().height / 2);

        exitText.setFont(font);
        exitText.setCharacterSize(40);
        exitText.setPosition(machine.app.window.getSize().x / 2, 465);
        exitText.setString("Exit");
        exitText.setOutlineThickness(1);
        exitText.setOutlineColor(sf::Color::Black);
        exitText.setOrigin(exitText.getLocalBounds().width / 2, exitText.getLocalBounds().height / 2);

        textSetup = true;
    }

    sf::Event event;
    sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(machine.app.window).x, sf::Mouse::getPosition(machine.app.window).y);


    while(machine.app.window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                machine.app.window.close();
                exit(0);

            case sf::Event::MouseMoved:
                if(machine.app.GetButtons()[0]->buttonSprite.getGlobalBounds().contains(mousePos))
                {

                    machine.app.GetButtons()[0]->updateDraw(sf::Color(150, 150, 150));

                    menuChoice = STARTGAME;
                    continue;
                }else{
                    machine.app.GetButtons()[0]->updateDraw(sf::Color::White);
                    menuChoice = NONE;
                }

                if(machine.app.GetButtons()[1]->buttonSprite.getGlobalBounds().contains(mousePos))
                {

                    machine.app.GetButtons()[1]->updateDraw(sf::Color(150, 150, 150));

                    menuChoice = SETUP;
                    continue;
                }else{
                    machine.app.GetButtons()[1]->updateDraw(sf::Color::White);
                    menuChoice = NONE;
                }

                if(machine.app.GetButtons()[2]->buttonSprite.getGlobalBounds().contains(mousePos))
                {

                    machine.app.GetButtons()[2]->updateDraw(sf::Color(150, 150, 150));

                    menuChoice = EXITGAME;
                    continue;
                }else{
                    machine.app.GetButtons()[2]->updateDraw(sf::Color::White);
                    menuChoice = NONE;
                }

            case sf::Event::MouseButtonReleased:
                if(event.mouseButton.button == sf::Mouse::Left){
                    if (menuChoice == STARTGAME) {

                        machine.MenuMusic.pause();

                        if (!machine.app.toggleMute) {
                            if (!machine.BackgroundMusic.openFromFile("MusicAndSound/Music/BackgroundMusic.wav")) {
                                std::cout << "Failed to load background music" << std::endl;
                            }
                            machine.BackgroundMusic.play();
                            machine.BackgroundMusic.setVolume(10.f);
                            machine.BackgroundMusic.setLoop(true);
                        }

                        machine.SetState(Machine::StateId::START);
                        machine.app.gameRun = false;
                    } else if (menuChoice == SETUP) {
                        std::cout << "Entered settings" << std::endl;
                        machine.SetState(Machine::StateId::SETTINGS);
                        machine.app.gameRun = false;
                    } else if (menuChoice == EXITGAME) {
                        std::cout << "Exiting.." << std::endl;
                        machine.app.gameRun = false;
                        exit(0);
                    }
                }

            default:
                break;
        }
    }


    machine.app.window.draw(menuText);
    machine.app.window.draw(startGameText);
    machine.app.window.draw(settingsText);
    machine.app.window.draw(exitText);

    machine.app.window.display();
    if(!machine.app.gameRun)
    {
        machine.app.mapObjects.clear();
        machine.app.deleteInstance();
    }
}
