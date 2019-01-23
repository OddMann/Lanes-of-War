//
// Created by Kringle on 19/10/2018.
//


#include "Node.h"
#include "Thor/Vectors.hpp"
#include "../Entities/Entity.h"
#include "../Entities/Building.h"
#include "../../App/App.h"
Node::Node(sf::Vector2f pos, int size, Map map) : Space(pos,2*size,map)
{
    this->radius = size;
    target[0] = nullptr;
    target[1] = nullptr;
    buildable[0] = false;
    buildable[1] = false;
    owner = -1;
    b = nullptr;

}
bool Node::contains(sf::Vector2f p)
{
    bool boolx = (p.x >= position.x - radius && p.x < position.x + radius);
    bool booly = (p.y >= position.y - radius && p.y < position.y + radius);
    return boolx && booly;
}
void Node::draw(sf::RenderWindow &window)
{
    sf::CircleShape circle(radius);
    float distsq = thor::squaredLength(position - sf::Vector2f(sf::Mouse::getPosition(window)));
    if(distsq < radius*radius)
        circle.setFillColor(sf::Color::Green);
    else
        circle.setFillColor(sf::Color::White);
    circle.setPosition(position);
    circle.setOrigin(radius,radius);
    window.draw(circle);
}

void Node::Upadate(sf::RenderWindow &window)
{

    sf::CircleShape circle(radius);

    circle.setOutlineThickness(2);
    if(contains({(float)sf::Mouse::getPosition(window).x,(float)sf::Mouse::getPosition(window).y}))
        circle.setOutlineColor({0,255,0,255});

    else
    {
        if(owner == 0)
            circle.setOutlineColor({0,0,255,64});
        else if(owner == 1)
            circle.setOutlineColor({255,0,0,64});
        else
            circle.setOutlineColor({255,255,255,64});
    }
    circle.setFillColor({255,255,255,64});

    if(b != nullptr)
    {
        if(b->GetState() == Entity::State::DEAD)
        {
            b = nullptr;
            owner = -1;
        }
        else
            owner = b->GetTeam().GetId();

    }
    else
        owner = -1;

    for(auto &bu: buildable)
        bu = false;

    if(owner == -1)
    {
        for(auto &n: neighbours)
            if(n->owner != -1)
                buildable[n->b->GetTeam().GetId()] = true;
    }




    circle.setPosition(position);
    circle.setOrigin(radius,radius);
    window.draw(circle);
}

