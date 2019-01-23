//
// Created by Kringla on 23.11.2018.
//

#ifndef KAPPAPRIDE_BUTTONTEXTURE_H
#define KAPPAPRIDE_BUTTONTEXTURE_H

#include "../Button.h"

class ButtonTexture : public Button{
public:
    ButtonTexture(sf::Vector2f pos, int x_size, int y_size, sf::Color color, std::string texture, Map map);

    bool hover(){return false;}
    bool click(){return false;}
};


#endif //KAPPAPRIDE_BUTTONTEXTURE_H
