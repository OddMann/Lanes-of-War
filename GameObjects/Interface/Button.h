//
// Created by OddMann on 25.10.2018.
//

#ifndef KAPPAPRIDE_BUTTON_H
#define KAPPAPRIDE_BUTTON_H

#include "Interface.h"
#include <functional>
class Team;
class Button: public Interface {

public:
    virtual obj_Type Type()const{return obj_Type::BUTTON;}
    sf::Texture buttonTexture;
    sf::Sprite buttonSprite;
    Button(sf::Vector2f pos, int x_size, int y_size, sf::Color color, std::string texture, Map map);
    void draw(sf::RenderWindow &window);
    void updateDraw(sf::Color color);

    int X_Size()const{return x_size;}
    int Y_Size()const{return y_size;}
    explicit Button(Map map);
    ~Button() = default;
    void update(Mouse &mouse, sf::RenderWindow &window)override;
    bool contains(sf::Vector2f object);


    virtual bool hover() = 0;
    virtual bool click() = 0;

protected:
    int target;
    int x_size;
    int y_size;
    sf::Text label;
    sf::Text textCost;
    sf::Font font;
    bool pressed;
    sf::Keyboard::Key key;
    float standardoThick;
    float oThick;
    sf::Color standardColor;
    sf::Color color;
};


#endif //KAPPAPRIDE_BUTTON_H
