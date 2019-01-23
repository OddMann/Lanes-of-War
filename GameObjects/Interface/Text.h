//
// Created by Kringla on 26.11.2018.
//

#ifndef KAPPAPRIDE_TEXT_H
#define KAPPAPRIDE_TEXT_H

#include "Interface.h"
#include <sstream>
class Text : public Interface{
public:
    Text(Map& map):Interface(map){}
    Text(sf::Vector2f pos, int charSize, Map& map);
    void draw(sf::RenderWindow &window)override;
    void update(sf::RenderWindow &window);
    void swap(Text& first, Text& second)
    {
        using std::swap;
        swap(first.charSize, second.charSize);
        swap(first.text, second.text);
        swap(first.font, second.font);
        swap(first.position, second.position);
    }
    Text& operator=(Text other)
    {
        swap(*this, other);
        return *this;
    }

    std::ostringstream buf;
private:
    int charSize;
    sf::Text text;
    sf::Font font;
};



#endif //KAPPAPRIDE_TEXT_H
