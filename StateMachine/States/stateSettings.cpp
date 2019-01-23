//
// Created by Kristian on 16.11.2018.
//

#include "stateSettings.h"

#define TOGGLEFPS 0
#define TOGGLEMUTE 1
#define BACK 2
#define NONE -1

void stateSettings::GoNext(Machine &machine)
{
    if(!machine.app.gameRun)
    {
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
        settingsHeader.setFont(font);
        settingsHeader.setCharacterSize(40);
        settingsHeader.setPosition(machine.app.window.getSize().x / 2, 150);
        settingsHeader.setString("Settings");
        settingsHeader.setOutlineThickness(1);
        settingsHeader.setOutlineColor(sf::Color::Black);
        settingsHeader.setOrigin(settingsHeader.getLocalBounds().width / 2, settingsHeader.getLocalBounds().height / 2);

        toggleFPS.setFont(font);
        toggleFPS.setCharacterSize(40);
        toggleFPS.setPosition(machine.app.window.getSize().x / 2, 225);
        toggleFPS.setString("Toggle FPS-counter");
        toggleFPS.setOutlineThickness(1);
        toggleFPS.setOutlineColor(sf::Color::Black);
        toggleFPS.setOrigin(toggleFPS.getLocalBounds().width / 2, toggleFPS.getLocalBounds().height / 2);

        toggleMUTE.setFont(font);
        toggleMUTE.setCharacterSize(40);
        toggleMUTE.setPosition(machine.app.window.getSize().x / 2, 350);
        toggleMUTE.setString("Toggle mute");
        toggleMUTE.setOutlineThickness(1);
        toggleMUTE.setOutlineColor(sf::Color::Black);
        toggleMUTE.setOrigin(toggleMUTE.getLocalBounds().width / 2, toggleMUTE.getLocalBounds().height / 2);

        back.setFont(font);
        back.setCharacterSize(40);
        back.setPosition(machine.app.window.getSize().x / 2, 465);
        back.setString("Back to menu");
        back.setOutlineThickness(1);
        back.setOutlineColor(sf::Color::Black);
        back.setOrigin(back.getLocalBounds().width / 2, back.getLocalBounds().height / 2);

        textSetup = true;
    }

    if (!machine.app.togglefps)
    {
        fpsHeader.setFont(font);
        fpsHeader.setCharacterSize(30);
        fpsHeader.setPosition((machine.app.window.getSize().x / 2) + 200, 220);
        fpsHeader.setFillColor(sf::Color::Red);
        fpsHeader.setString("OFF");
        machine.app.window.draw(fpsHeader);
    }
    else if (machine.app.togglefps)
    {
        fpsHeader.setFillColor(sf::Color::Green);
        fpsHeader.setString("ON");
        machine.app.window.draw(fpsHeader);
    }

    if (!machine.app.toggleMute)
    {
        muteHeader.setFont(font);
        muteHeader.setCharacterSize(30);
        muteHeader.setPosition((machine.app.window.getSize().x / 2) + 200, 340);
        muteHeader.setFillColor(sf::Color::Red);
        muteHeader.setString("OFF");
        machine.app.window.draw(muteHeader);
    }
    else if (machine.app.toggleMute)
    {
        muteHeader.setFillColor(sf::Color::Green);
        muteHeader.setString("ON");
        machine.app.window.draw(muteHeader);
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

                    menuChoice = TOGGLEFPS;
                    continue;
                }else{
                    machine.app.GetButtons()[0]->updateDraw(sf::Color::White);
                    menuChoice = NONE;
                }

                if(machine.app.GetButtons()[1]->buttonSprite.getGlobalBounds().contains(mousePos))
                {

                    machine.app.GetButtons()[1]->updateDraw(sf::Color(150, 150, 150));

                    menuChoice = TOGGLEMUTE;
                    continue;
                }else{
                    machine.app.GetButtons()[1]->updateDraw(sf::Color::White);
                    menuChoice = NONE;
                }

                if(machine.app.GetButtons()[2]->buttonSprite.getGlobalBounds().contains(mousePos))
                {

                    machine.app.GetButtons()[2]->updateDraw(sf::Color(150, 150, 150));

                    menuChoice = BACK;
                    continue;
                }else{
                    machine.app.GetButtons()[2]->updateDraw(sf::Color::White);
                    menuChoice = NONE;
                }

            case sf::Event::MouseButtonReleased:
                if(event.mouseButton.button == sf::Mouse::Left){
                    if (menuChoice == TOGGLEFPS) {

                        machine.app.togglefps = !machine.app.togglefps;

                    } else if (menuChoice == TOGGLEMUTE) {
                        machine.app.toggleMute = !machine.app.toggleMute;

                        if (!machine.app.toggleMute)
                        {
                            machine.MenuMusic.play();
                        }
                        else if (machine.app.toggleMute)
                        {
                            machine.MenuMusic.stop();
                        }

                    } else if (menuChoice == BACK) {
                        machine.MenuMusic.pause();
                        machine.SetState(Machine::StateId::MENU);
                        run = false;
                        machine.app.gameRun = false;
                    }
                }

            default:
                break;
        }
    }


    machine.app.window.draw(settingsHeader);
    machine.app.window.draw(toggleFPS);
    machine.app.window.draw(toggleMUTE);
    machine.app.window.draw(back);

    machine.app.window.display();
    if(!machine.app.gameRun)
    {
        machine.app.mapObjects.clear();
        machine.app.deleteInstance();
    }
}
