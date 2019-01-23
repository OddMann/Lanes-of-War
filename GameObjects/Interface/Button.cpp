//
// Created by OddMann on 25.10.2018.
//

#include "Button.h"
#include "../../App/App.h"

Button::Button(Map map) : Interface(map)
{}

Button::Button(sf::Vector2f pos, int x_size, int y_size, sf::Color color, std::string texture, Map map) : Interface(map)
{
    if(!buttonTexture.loadFromFile("res/InterfaceTextures/buttonTemplate.png"))
    {
        std::cout << "Failed to load menubutton texture" << std::endl;
    }

    if(texture == "MENUBUTTON"){
        buttonSprite.setTextureRect(sf::IntRect(0, 0, 593, 59));
    }else if(texture == "SQUAREBUTTON"){
        buttonSprite.setTextureRect(sf::IntRect(0, 59, 30, 30));
    } else if(texture == "RIGHTBUTTON"){
        buttonSprite.setTextureRect(sf::IntRect(30, 59, 59, 59));
    } else if(texture == "LEFTBUTTON") {
        buttonSprite.setTextureRect(sf::IntRect(89, 59, 59, 59));
    } else if(texture == "UNITONE"){
        buttonSprite.setTextureRect(sf::IntRect(148, 59, 40, 40));
    } else if(texture == "UNITTWO") {
        buttonSprite.setTextureRect(sf::IntRect(188, 59, 40, 40));
    } else if(texture == "UNITTHREE") {
        buttonSprite.setTextureRect(sf::IntRect(228, 59, 40, 40));
    }

    this->x_size = x_size;
    this->y_size = y_size;
    this->position = pos;

    this->Id = Button::nextId++;
    this->Interface_Id = Button::nextI_Id++;

    this->standardoThick = oThick;
    this->color = color;
}

bool Button::contains(sf::Vector2f object)
{
    if(object.x < position.x+x_size && object.x > position.x)
    {
        if(object.y < position.y+y_size && object.y > position.y)
        {
            return true;
        }
    }
    return false;
}
void Button::update(Mouse &mouse, sf::RenderWindow &window)
{
    draw(window);
    if(contains(mouse.pos()))
    {
        oThick = 5.0f;
        if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            click();
    }
    else
        oThick = standardoThick;
    if(hover())
        color = standardColor;
    else
        color = {155,155,155};

}
void Button::draw(sf::RenderWindow &window)
{
    buttonSprite.setTexture(buttonTexture);
    buttonSprite.setColor(color);
    buttonSprite.setOrigin(buttonSprite.getLocalBounds().width / 2 , buttonSprite.getLocalBounds().height / 2);
    buttonSprite.setPosition(position);
    window.draw(buttonSprite);
}

void Button::updateDraw(sf::Color color)
{
    this->color = color;
}
