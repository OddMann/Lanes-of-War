//
// Created by Kringla on 13.11.2018.
//

#ifndef KAPPAPRIDE_INTERFACE_H
#define KAPPAPRIDE_INTERFACE_H

#include "SFML/Graphics.hpp"
#include "../Object.h"
#include "../Mouse.h"

class Interface: public Object{
public:
    explicit Interface(Map& map);
    int GetInterface_Id() { return Interface_Id;}
    virtual void update(Mouse &mouse, sf::RenderWindow &window){}
protected:
    int Interface_Id;
    static int nextI_Id;
};


#endif //KAPPAPRIDE_INTERFACE_H
