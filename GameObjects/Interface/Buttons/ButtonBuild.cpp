//
// Created by Kringle on 07/12/2018.
//

#include "ButtonBuild.h"
#include "../../Entities/Building.h"
#include "../../../App/App.h"
ButtonBuild::ButtonBuild(sf::Vector2f pos, sf::Keyboard::Key key, int x_size, int y_size, float oThick, sf::Color color, int target, Map map, Team& team) : Button(map)
{
    this->x_size = x_size;
    this->y_size = y_size;
    this->position = pos;
    this->key = key;
    this->team = &team;
    this->Id = Button::nextId++;
    this->Interface_Id = Button::nextI_Id++;
    this->target = target;
    this->standardoThick = oThick;
    this->standardColor = color;
    this->pressed = false;


    if ( !font.loadFromFile("fonts/GIL.TTF"))
        std::cerr << "failed to load font" << std::endl;
    label.setFont(font);
    label.setCharacterSize(10);
    label.setOrigin({-2,-2});
    label.setPosition(position);
    label.setFillColor(sf::Color::Black);
    label.setString(Building::Types[target].name);
    std::ostringstream txtC;
    textCost.setFont(font);
    textCost.setCharacterSize(10);
    textCost.setOrigin({-2,-26});
    textCost.setPosition(position);
    textCost.setFillColor(sf::Color::Black);
    txtC << Building::Types[target].cost;
    textCost.setString(txtC.str());
    txtC.clear();
}
ButtonBuild::~ButtonBuild()
{
    team = nullptr;
}
bool ButtonBuild::hover()
{
    return (Building::Types[target].cost <= team->Money());
}
bool ButtonBuild::click()
{
    if(hover())
    {
        team->CreateBuildingTeam(target, team->Selectt(), false);
        return true;
    }
    return false;
}
void ButtonBuild::update(Mouse &mouse, sf::RenderWindow &window)
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
        color = {150,150,255};
    else
        color = {155,155,170};

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
void ButtonBuild::draw(sf::RenderWindow &window)
{
    sf::RectangleShape button(sf::Vector2f(x_size, y_size));
    button.setFillColor(color);
    button.setOutlineThickness(oThick);
    button.setOutlineColor(ocol);
    button.setPosition(position);
    window.draw(button);
    window.draw(label);
    window.draw(textCost);
}