//
// Created by Kringla on 23.11.2018.
//

#include "ButtonTexture.h"
ButtonTexture::ButtonTexture(sf::Vector2f pos, int x_size, int y_size, sf::Color color, std::string texture, Map map) : Button(map)
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