//
// Created by Kringle on 15/11/2018.
//

#include "App.h"



Team::Team(int money, int income, int spawn, App& app) : app(app), textMoney(app.map), textIncome(app.map)
{
    Id = next_Id++;
    this->money = money;
    this->baseIncome = income;
    this->income = 0;
    this->spawn = app.GetNodes()[spawn];
    teamColor = colors[Id];
    uiset = {{20,580},{20,620},{20,660},{60,580},{60,620},{60,660},{100,580},{100,620},{100,660}};
    keys = app.keysets[Id];
    CreateBuildingTeam(0,this->spawn, true);
    target = nullptr;
    selected = nullptr;
    mouse = new Mouse(app.window, app.map);
    sf::Vector2f textPos = {(float)20+(Id*1120),50};
    sf::Vector2f textPos2 = {(float)20+(Id*1120),90};
    textMoney = {textPos, 20 ,app.map};
    textIncome = {textPos2, 20 ,app.map};
    for(auto b: Building::Types)
    {
        buildCount[b.first] = 0;
    }
}



void Team::CreateBuildingTeam(int Id, Node* node, bool base)
{
    //int sp = spawns[space];
    auto b_t = Building::Types[Id];
    if(money >= b_t.cost || base)
    {
        auto b = std::make_unique<Building>(b_t, *node, *this, base, app.map);
        node->b = b.get();
        buildCount[Id]++;
        if(!base)
            money -= b_t.cost;
        app.Entities.push_back(std::move(b));
    }

}
void Team::CreateButton(Building_p b_p, int x_size, int y_size, float oThick, sf::Color color, int x, int y, sf::Keyboard::Key key)
{

    //auto button = new ButtonUnit(uiset[Uid], x_size, y_size, oThick, teamColor, Uid, app.map, *this);
    auto button = new ButtonBuild({(float)x,(float)y}, key, x_size, y_size, oThick, color, b_p.first, app.map, *this);
    buttons.push_back(button);
}

void Team::Selected()
{
    if(selected == nullptr)
        return;
    for(auto &n: app.GetNodes())
    {
        if(n->contains(mouse->pos()))
        {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
            {
                if(selected != n)
                {
                    selected->Target(Id, n);
                } else {
                    selected->Target(Id, nullptr);
                }
                selected = nullptr;
                return;
            }

        }
    }
    if(selected->owner == this->Id)
    {
        for(auto &b: selected->b->GetButtons())
            b->update(*mouse, app.window);
    }
}
bool Team::inSpace()
{
    for(auto &n: app.GetNodes())
    {
        if(n->contains(mouse->pos()))
        {
            Select(*n);
            return true;
        }
    }
    return false;
}

void Team::Select()
{

    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        inSpace();
    }
}

bool Team::tick()
{
    if(base->GetState() == Entity::State::DEAD)
    {

        std::cout << "Team "<< Id <<" has died;";
        //TODO: set team to defeated
        app.loser = Id;
        base->Alive(false);
        base = nullptr;
         return false;
    }


    Selected();
    Select();


    if(selected == nullptr)
    {}
    else if(selected->buildable[0])
    {
        for(auto b: buttons)
        {
            b->update(*mouse, app.window);
        }
    }

    else if(selected->b != nullptr && selected->owner == this->Id)
    {
        for(auto b: selected->b->GetButtons())
        {
            b->update(*mouse, app.window);
        }
    }

    income += baseIncome;
    money += income;
    textMoney.buf << "Money: " << (int)money;
    textMoney.update(app.window);
    textIncome.buf << "Income: " << income;
    textIncome.update(app.window);
    income = 0;
    return true;
}

int Team::next_Id = 0;

