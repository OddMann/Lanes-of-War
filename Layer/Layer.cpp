//
// Created by OddMann on 02.11.2018.
//

#include "Layer.h"
#include "../Map/Map.h"

void Layer::draw(sf::RenderWindow& window)
{

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width ; x++)
        {
            unsigned int gid = tilemap[x + y * width];

            if (gid == 0)
                continue;

            sf::Sprite sprite;

            map.setSpriteTextureFromGid(sprite, gid);
            sprite.setPosition((float)(x * map.getTileWidth()), (float)(y * map.getTileHeight()));

            window.draw(sprite);
        }
    }
}