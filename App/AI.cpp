//
// Created by Kringle on 29/11/2018.
//

#include "AI.h"
#include "Thor/Vectors.hpp"
AI::AI(int money, int income, int spawn, App& app) : Team(money, income, spawn, app)
{
    phase = Phase::BOOM;
    selected = app.GetNodes()[10];
    selected->Target(Id,app.GetNodes()[0]);
    selected = app.GetNodes()[16];
    selected->Target(Id,app.GetNodes()[0]);
    selected = app.GetNodes()[6];
    selected->Target(Id,app.GetNodes()[0]);
    closestNode.resize(1);
}
bool AI::boom()
{



    if(income < 2.5)
    {
        for(auto n: app.GetNodes())
        {
            if(n->buildable[1])
            {
                sf::Vector2f diff = spawn->pos()-n->pos();

                float d = thor::squaredLength(diff);
                closestNode.add(d,n);
            }

        }
        if(!closestNode.empty())
        {
            auto n = closestNode.pop();
            if(money >= Building::Types[1].cost)
            {
                CreateBuildingTeam(1,n, false);
            }
        }
    }
    else if(income < 10)
    {
        for(auto n: app.GetNodes())
        {
            if(n->owner == 1 && n->b->Type_Id() == 1)
            {
                if(n->b->GetButton(0)->hover())
                {
                    sf::Vector2f diff = spawn->pos()-n->pos();

                    float d = thor::squaredLength(diff);
                    closestNode.add(d,n);
                }
            }

        }
        if(!closestNode.empty())
        {
            auto n = closestNode.pop();
            n->b->GetButton(0)->click();
        }
    }
    else if(buildCount[2] < 3 && money < 1000)
    {
        for(auto n: app.GetNodes())
        {
            if(n->buildable[1])
            {
                sf::Vector2f diff = spawn->pos()-n->pos();

                float d = thor::squaredLength(diff);
                closestNode.add(d,n);
            }

        }
        if(!closestNode.empty())
        {
            auto n = closestNode.pop();
            if(money >= Building::Types[2].cost)
            {
                CreateBuildingTeam(2,n, false);
                n->Target(Id, app.GetNodes()[0]);

            }
        }
    }
    //else if(buildCount[2] < 6 && money < 1000)
    //{
    //    for(auto n: app.GetNodes())
    //    {
    //        if(n->buildable[1])
    //        {
    //            sf::Vector2f diff = spawn->pos()-n->pos();
//
    //            float d = thor::squaredLength(diff);
    //            closestNode.add(d,n);
    //        }
//
    //    }
    //    if(!closestNode.empty())
    //    {
    //        auto n = closestNode.pop();
    //        if(money >= Building::Types[2].cost)
    //        {
    //            CreateBuildingTeam(2,n, false);
    //            n->Target(Id, app.GetNodes()[0]);
//
    //        }
    //    }
    //}
    else
    {
        phase = RUSH;
    }

    return true;
}
bool AI::rush()
{

    if(selected->Target(Id) == app.GetNodes()[0])
    {
        selected->Target(Id, app.GetNodes()[10]);
    }
    else if(selected->Target(Id) == app.GetNodes()[10])
    {
        selected->Target(Id, app.GetNodes()[16]);
    }
    else if(selected->Target(Id) == app.GetNodes()[14])
    {
        selected->Target(Id, app.GetNodes()[0]);
    }
    else
        selected->Target(Id, app.GetNodes()[0]);

    for(auto n: app.GetNodes())
    {
        if(n->owner == 1)
        {
            if(n->b->Type_Id() == 2 && n->b->spawnQempty())
            {
                if(money <= 1000)
                    n->b->GetButton(0)->click();
                else
                {
                    n->b->GetButton(racks_order.front())->click();
                    auto tmp = racks_order.front();
                    racks_order.pop_front();
                    racks_order.emplace_back(tmp);

                }
            }
        }
    }

    if(buildCount[2] < 3 && money < 1000)
    {
        phase = BOOM;
    }
    return true;
}
bool AI::mass()
{

    return true;
}
bool AI::tick()
{

    if(base->GetState() == Entity::State::DEAD)
    {

        std::cout << "Team "<< Id <<" has died;";
        //TODO: set team to defeated
        base->Alive(false);
        base = nullptr;
        return false;
    }
    income += baseIncome;
    money += income;
    switch (phase)
    {
        case BOOM:
            boom();
            break;
        case RUSH:
            rush();
            break;
        case MASS:
            mass();
            break;

    }
    //for(auto b: buttons)
    textMoney.buf << "Money: " << (int)money;
    textMoney.update(app.window);
    textIncome.buf << "Income: " << income;
    textIncome.update(app.window);
    income = 0;
    return true;
}