//
// Created by Kringla on 18.11.2018.
//

#ifndef KAPPAPRIDE_BUTTONUNIT_H
#define KAPPAPRIDE_BUTTONUNIT_H

#include "../Button.h"
class Building;
class ButtonUnit : public Button{
public:
    ButtonUnit(sf::Vector2f pos, sf::Keyboard::Key key, int x_size, int y_size, float oThick, sf::Color color, int target, Map map, Team& team, Building& b);

    ~ButtonUnit();
    void draw(sf::RenderWindow &window);
    void update(Mouse &mouse, sf::RenderWindow &window)override;
    bool click()override;
    bool hover()override;
private:
    Building* b;
    Team* team;
    sf::Color ocol;
};


#endif //KAPPAPRIDE_BUTTONUNIT_H
