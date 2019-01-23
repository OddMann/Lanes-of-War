//
// Created by OddMann on 02.11.2018.
//

#include "Sprite.h"
#include "../Map/Map.h"

void Sprite::process(float deltaTime)
{
    auto& animation = map.getAnimation(gid);

    if (animation->empty())
        return;

    if (clock.getElapsedTime().asMilliseconds() < (*animation)[frame].duration)
        return;

    if(++frame >= (int)animation->size())
        frame = 0;

    clock.restart();
}

void Sprite::draw(sf::RenderWindow& window)
{
    sf::Sprite sprite;
    map.setSpriteTextureFromGid(sprite, gid, frame);
    sprite.setPosition((float)x, (float)y);

    window.draw(sprite);

}