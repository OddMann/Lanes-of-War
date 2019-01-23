//
// Created by Kristian on 14.12.2018.
//

#include "statePause.h"

void statePause::GoNext(Machine &machine) {
    
    if (!run) {
        machine.app.gameRun = true;
    }

    if (!font.loadFromFile("Fonts/GIL.ttf"))
        std::cerr << "Failed to load font" << std::endl;

    machine.app.clock.restart();

    machine.app.mapTick(machine.app.window, machine.app.mapObjects, deltaTime);
    deltaTime = machine.app.clock.getElapsedTime().asSeconds();
    machine.app.clock.restart();

    if (!textSetup) {
        pauseText.setFont(font);
        pauseText.setCharacterSize(40);
        pauseText.setPosition(machine.app.window.getSize().x / 2, 150);
        pauseText.setString("Paused");
        pauseText.setFillColor(sf::Color::White);
        pauseText.setOutlineColor(sf::Color::Black);
        pauseText.setOutlineThickness(1);
        pauseText.setOrigin(pauseText.getLocalBounds().width / 2, pauseText.getLocalBounds().height / 2);

        exitText.setFont(font);
        exitText.setCharacterSize(40);
        exitText.setPosition(machine.app.window.getSize().x / 2, 350);
        exitText.setString("Press 'Enter' to continue");
        exitText.setFillColor(sf::Color::White);
        exitText.setOutlineColor(sf::Color::Black);
        exitText.setOutlineThickness(1);
        exitText.setOrigin(exitText.getLocalBounds().width / 2, exitText.getLocalBounds().height / 2);

        menuText.setFont(font);
        menuText.setCharacterSize(40);
        menuText.setPosition(machine.app.window.getSize().x / 2, 465);
        menuText.setString("Press 'Escape' to go back to menu");
        menuText.setFillColor(sf::Color::White);
        menuText.setOutlineColor(sf::Color::Black);
        menuText.setOutlineThickness(1);
        menuText.setOrigin(menuText.getLocalBounds().width / 2, menuText.getLocalBounds().height / 2);

        textSetup = true;
    }

    sf::Event event;

    while (machine.app.window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                machine.app.window.close();
                exit(0);

            case sf::Event::KeyReleased:
            {
                if (event.key.code == sf::Keyboard::Enter) {

                    if (!machine.app.map.loadFromFile("MapData/Map.json")) {
                        std::cout << "Failed to load map data" << std::endl;
                    }
                    machine.app.mapCopyObjects();
                    machine.app.gameRun = true;
                    machine.SetState(Machine::StateId::START);
                }

                if (event.key.code == sf::Keyboard::Escape) {

                    machine.app.gameRun = false;
                    run = false;
                    machine.app.deleteInstance();
                    machine.app.mapObjects.clear();
                    machine.SetState(Machine::StateId::MENU);
                }
        }

        default:
            break;
    }
}
    machine.app.window.clear({200,200,200});

    sf::Vector2f size = {(float)machine.app.window.getSize().x,(float)machine.app.window.getSize().y};
    sf::RectangleShape pausescreen(size);
    pausescreen.setFillColor({0,0,0,150});
    pausescreen.setPosition(0,0);
    for (auto& mapObject: machine.app.mapObjects)
    {
        mapObject->draw(machine.app.window);
    }
    for(auto& e: machine.app.GetEntities())
    {
        if(e->Alive())
        {
            e->draw(machine.app.window);
        }
    }
    machine.app.window.draw(pausescreen);
    machine.app.window.draw(pauseText);
    machine.app.window.draw(exitText);
    machine.app.window.draw(menuText);

    machine.app.window.display();
    if(!machine.app.gameRun)
    {
        machine.app.mapObjects.clear();
        machine.app.deleteInstance();
    }
}