//
// Created by Kringle on 07/12/2018.
//

#ifndef KAPPAPRIDE_BUTTONBUILD_H
#define KAPPAPRIDE_BUTTONBUILD_H

#include "../Button.h"

class ButtonBuild : public Button{
public:
    ButtonBuild(sf::Vector2f pos, sf::Keyboard::Key key, int x_size, int y_size, float oThick, sf::Color color, int target, Map map, Team& team);

    ~ButtonBuild();
    void draw(sf::RenderWindow &window);
    void update(Mouse &mouse, sf::RenderWindow &window)override;
    bool click()override;
    bool hover()override;
private:
    Team* team;
    sf::Color ocol;
};


#endif //KAPPAPRIDE_BUTTONBUILD_H
