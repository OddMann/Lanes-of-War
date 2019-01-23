//
// Created by Kringla on 26.11.2018.
//

#include "Text.h"
Text::Text(sf::Vector2f pos, int charSize, Map& map) : Interface(map)
{
    this->charSize = charSize;
    this->position = pos;
    this->Id = this->nextId;
    this->Interface_Id = this->nextI_Id;


}
void Text::update(sf::RenderWindow &window)
{
    draw(window);
}
void Text::draw(sf::RenderWindow &window)
{



    if ( !font.loadFromFile("fonts/GIL.ttf"))
        std::cerr << "failed to load font" << std::endl;

    text.setFont(font);
    text.setCharacterSize(charSize);
    text.setPosition(position);
    text.setFillColor(sf::Color::White);
    text.setOutlineThickness(1);
    text.setOutlineColor(sf::Color::Black);
    text.setString(buf.str());
    window.draw(text);
    buf.clear();
    buf = std::ostringstream();
}