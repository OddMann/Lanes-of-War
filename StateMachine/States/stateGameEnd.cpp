//
// Created by OddMann on 16.12.2018.
//

#include "stateGameEnd.h"
#include "../Machine.h"
#include "../../App/App.h"
#include "../../GameObjects/Object.h"
#include "../../Layer/Layer.h"
#include "../../Sprite/Sprite.h"

#define STARTGAME   0
#define MENUCHOICE  1
#define NONE       -1

void stateGameEnd::GoNext(Machine &machine)
{
    if(!run)
    {
        if (!machine.app.map.loadFromFile("MapData/Menu.json")) {
            std::cout << "Failed to load map data" << std::endl;
        }

        machine.app.mapCopyObjects();

        machine.app.CreateButton({640 , 240}, 350, 80, sf::Color::White, "MENUBUTTON");  //Interface_Id 0
        machine.app.CreateButton({640 , 360}, 350, 80, sf::Color::White, "MENUBUTTON");  //Interface_Id 1

        machine.app.GetButtons()[0]->updateDraw(sf::Color::White);
        machine.app.GetButtons()[1]->updateDraw(sf::Color::White);

        if (!font.loadFromFile("Fonts/GIL.ttf"))
            std::cerr << "Failed to load font" << std::endl;

        topText.setFont(font);
        topText.setCharacterSize(40);
        topText.setPosition(machine.app.window.getSize().x / 2, 150);
        topText.setOutlineThickness(2);
        topText.setOutlineColor(sf::Color::Black);

        startGameText.setFont(font);
        startGameText.setCharacterSize(40);
        startGameText.setPosition(machine.app.window.getSize().x / 2, 225);
        startGameText.setOutlineThickness(1);
        startGameText.setOutlineColor(sf::Color::Black);

        if(machine.app.GetLoser() == 0){
            std::cout << "Player lost" << std::endl;
            startGameText.setString("Retry");
            topText.setString("YOU LOST!\n There is a Readme");
        } else if(machine.app.GetLoser() == 1) {
            std::cout << "Player won 1" << std::endl;
            startGameText.setString("Start new game");
            topText.setString("YOU WON!");
        } else {
            std::cout << "Player won 2" << std::endl;
            startGameText.setString("Start new game");
            topText.setString("YOU WON!");
        }

        topText.setOrigin(topText.getLocalBounds().width / 2, topText.getLocalBounds().height / 2);

        startGameText.setOrigin(startGameText.getLocalBounds().width / 2, startGameText.getLocalBounds().height / 2);

        menuText.setFont(font);
        menuText.setCharacterSize(40);
        menuText.setPosition(machine.app.window.getSize().x / 2, 350);
        menuText.setString("Menu");
        menuText.setOrigin(menuText.getLocalBounds().width / 2, menuText.getLocalBounds().height / 2);
        menuText.setOutlineThickness(1);
        menuText.setOutlineColor(sf::Color::Black);


        run = true;
    }



    machine.app.clock.restart();

    machine.app.window.clear(sf::Color::White);

    machine.app.mapTick(machine.app.window, machine.app.mapObjects, deltaTime);
    deltaTime = machine.app.clock.getElapsedTime().asSeconds();
    machine.app.clock.restart();

    for (auto& b: machine.app.GetButtons())
    {
        b->draw(machine.app.window);
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

                    menuChoice = MENUCHOICE;
                    continue;
                }else{
                    machine.app.GetButtons()[1]->updateDraw(sf::Color::White);
                    menuChoice = NONE;
                }

            case sf::Event::MouseButtonReleased:
                if(event.mouseButton.button == sf::Mouse::Left){
                    if (menuChoice == STARTGAME) {

                        machine.MenuMusic.pause();

                        if (!machine.BackgroundMusic.openFromFile("MusicAndSound/Music/BackgroundMusic.wav")) {
                            std::cout << "Failed to load background music" << std::endl;
                        }
                        machine.BackgroundMusic.play();
                        machine.BackgroundMusic.setVolume(10.f);
                        machine.BackgroundMusic.setLoop(true);

                        machine.SetState(Machine::StateId::START);
                        run = false;
                    } else if (menuChoice == MENUCHOICE) {
                        std::cout << "Entered settings" << std::endl;
                        machine.SetState(Machine::StateId::MENU);
                        run = false;
                    }
                }

            default:
                break;
        }
    }

    machine.app.window.draw(topText);
    machine.app.window.draw(startGameText);
    machine.app.window.draw(menuText);

    machine.app.window.display();
    if(!run)
    {
        machine.app.mapObjects.clear();
        machine .app.deleteInstance();
    }
}