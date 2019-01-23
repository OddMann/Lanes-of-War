//
// Created by Kringla on 14.12.2018.
//

#ifndef KAPPAPRIDE_BUTTONUPGRADE_H
#define KAPPAPRIDE_BUTTONUPGRADE_H

#include "../Button.h"
#include "../../Effects/Upgrade.h"
class Building;
class ButtonUpgrade: public Button
{
public:
    ButtonUpgrade(sf::Vector2f pos, sf::Keyboard::Key key, int x_size, int y_size, float oThick, sf::Color color, int target, Map map, Team& team, void* t);

    ~ButtonUpgrade();
    void draw(sf::RenderWindow &window);
    void update(Mouse &mouse, sf::RenderWindow &window)override;
    bool click()override;
    bool hover()override;
private:
    Upgrade* u;
    Team* team;
    sf::Text textRank;
    sf::Color ocol;
    void *t;
};



#endif //KAPPAPRIDE_BUTTONUPGRADE_H
