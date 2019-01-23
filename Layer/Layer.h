//
// Created by OddMann on 02.11.2018.
//

#ifndef KAPPAPRIDE_LAYER_H
#define KAPPAPRIDE_LAYER_H

#include <string>
#include "../GameObjects/Object.h"


class Layer : public Object {

    friend class Map;

public:
    explicit Layer(Map& map) : Object(map) {}
    ~Layer() { delete[] tilemap; }

    void draw(sf::RenderWindow& window) override;

protected:
    int id = 0;
    std::string name;
    int width = 0;
    int height = 0;
    bool visible = false;
    unsigned int* tilemap = nullptr;
};


#endif //KAPPAPRIDE_LAYER_H
