//
// Created by Kringla on 14.12.2018.
//

#include "ButtonUpgrade.h"
#include "../../Entities/Building.h"
#include "../../../App/App.h"
ButtonUpgrade::ButtonUpgrade(sf::Vector2f pos, sf::Keyboard::Key key, int x_size, int y_size, float oThick, sf::Color color, int target, Map map, Team& team, void* t) : Button(map)
{
    this->x_size = x_size;
    this->y_size = y_size;
    this->position = pos;
    this->key = key;
    this->team = &team;
    this->Id = Button::nextId++;
    this->Interface_Id = Button::nextI_Id++;
    this->t = t;
    Upgrade_t up = Upgrade::Types[target];
    auto u = new Upgrade(up, t, map);
    this->u = u;
    this->target = target;
    this->standardoThick = oThick;
    this->standardColor = color;
    std::ostringstream txtR;
    std::ostringstream txtC;

    if ( !font.loadFromFile("fonts/GIL.TTF"))
        std::cerr << "failed to load font" << std::endl;
    label.setFont(font);
    label.setCharacterSize(10);
    label.setOrigin({-2,-2});
    label.setPosition(position);
    label.setFillColor(sf::Color::Black);
    label.setString(Upgrade::Types[target].name);
    textRank.setFont(font);
    textRank.setCharacterSize(10);
    textRank.setOrigin({-30,-26});
    textRank.setPosition(position);
    textRank.setFillColor(sf::Color::Black);
    txtR << u->Rank;
    textRank.setString(txtR.str());
    txtR.clear();
    textCost.setFont(font);
    textCost.setCharacterSize(10);
    textCost.setOrigin({-2,-26});
    textCost.setPosition(position);
    textCost.setFillColor(sf::Color::Black);
    txtC << u->cost;
    textCost.setString(txtC.str());
    txtC.clear();
}
ButtonUpgrade::~ButtonUpgrade()
{
    team = nullptr;
    delete(u);
    u = nullptr;
}
bool ButtonUpgrade::hover()
{

    if(u->Rank >= u->Max_Rank)
    {
        return false;
    }
    else if(u->cost <= team->Money())
    {
        return true;
    }
    return false;
}
bool ButtonUpgrade::click()
{
    if(hover())
    {
        team->Money(-u->cost);
        u->funct();
        int newCost = (int)(u->cost * 1.5f)/10*10;
        u->cost = newCost;
        std::ostringstream txtR;
        std::ostringstream txtC;
        txtR << u->Rank;
        txtC << u->cost;
        textRank.setString(txtR.str());
        textCost.setString(txtC.str());
        return true;
    }
    return false;
}
void ButtonUpgrade::update(Mouse &mouse, sf::RenderWindow &window)
{
    draw(window);
    if(contains(mouse.pos()))
    {
        ocol = sf::Color::White;
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            click();
    }
    else
    {
        oThick = standardoThick;
        ocol = sf::Color::Black;
    }
    if(hover())
        color = {150,255,150};
    else
        color = {155,170,155};
    if(sf::Keyboard::isKeyPressed(key))
    {
        if(!pressed)
        {
            click();
            if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
                pressed = true;
        }
    }
    else
        pressed = false;

}
void ButtonUpgrade::draw(sf::RenderWindow &window)
{
    sf::RectangleShape button(sf::Vector2f(x_size, y_size));
    button.setFillColor(color);
    button.setOutlineThickness(oThick);
    button.setOutlineColor(ocol);
    button.setPosition(position);
    window.draw(button);
    window.draw(label);
    window.draw(textRank);
    window.draw(textCost);
}