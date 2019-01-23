//
// Created by Kringle on 19/10/2018.
//
#include <iostream>
#include "stateStart.h"
#include "../../App/App.h"
#include "../Machine.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"


void stateStart::GoNext(Machine &machine)
{
    if(!machine.app.gameRun)
    {
        GameInit(machine.app);
    }
    machine.SetState(GameLoop(machine.app));
}

void stateStart::GameInit(App &app)
{

    app.makeMap();

    app.ImportUnit();
    app.ImportBuilding();
    app.ImportAbility();
    app.ImportUpgrade();
    app.CreateTeam();
    if (!app.map.loadFromFile("MapData/Map.json"))
    {
        std::cout << "Failed to load map data" << std::endl;
    }



    app.mapCopyObjects();

    app.gameRun = true;
}
Machine::StateId stateStart::GameLoop(App &app)
{

    sf::Event event;

    app.clock.restart();

    app.window.clear({100,100,100});


    app.mapTick(app.window, app.mapObjects, deltaTime);
    deltaTime = app.clock.getElapsedTime().asSeconds();
    app.clock.restart();


    for(auto& n: app.GetNodes())
        n->Upadate(app.window);

    for(auto& e: app.GetEntities())
    {
        if(e->Alive())
        {
            e->update(app.GetEntities(), app.window);
        }
    }


    app.GetEntities().remove_if([](auto& o){return !o->Alive();});


    for (auto& b: app.GetButtons())
    {
        b->draw(app.window);
    }

    int alive = 0;
    for (auto &t: app.GetTeams())
    {
        if(t->tick())
            alive++;
    }

    app.GetTeams()[0]->GetMouse().draw(app.window);


    if (app.togglefps)
    {
        fpsCounter(app);
    }
    if(alive == 1)
    {
        app.gameRun = false;

        app.deleteInstance();
        app.mapObjects.clear();
        return Machine::StateId::END;
    }



    app.window.display();

    while(app.window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                app.window.close();
                exit(0);
            case sf::Event::KeyReleased:
                if(event.key.code == sf::Keyboard::Escape)
                {
                    return Machine::StateId::PAUSE;
                }
                break;
            default:
                break;
        }

    }


    return Machine::StateId::START;
}

void stateStart::fpsCounter(App &app)
{
        time = clock.getElapsedTime();
        fpscount = 1.0f / time.asSeconds();
        clock.restart().asSeconds();

        std::ostringstream ss;
        ss << "FPS: " << (int)fpscount;

        if ( !font.loadFromFile("fonts/comic.ttf"))
            std::cerr << "failed to load font" << std::endl;

        fps.setFont(font);
        fps.setCharacterSize(20);
        fps.setPosition(10, 10);
        fps.setFillColor(sf::Color::White);
        fps.setOutlineThickness(1);
        fps.setOutlineColor(sf::Color::Black);
        fps.setString(ss.str());
        app.window.draw(fps);
}