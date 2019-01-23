//
// Created by OddMann on 02.11.2018.
//

#include <jsoncpp/json/json.h>
#include <fstream>
#include "Map.h"
#include <SFML/Graphics/Sprite.hpp>
#include <memory>
#include "../Layer/Layer.h"
#include "../Sprite/Sprite.h"
#include "../GameObjects/Object.h"

bool Map::loadFromFile(const std::string& filename)
{
    tilesets.clear();
    animations.clear();
    layers.clear();
    sprites.clear();

    Json::Value root;
    Json::Reader reader;

    std::ifstream file(filename);

    bool parsingSuccessful = reader.parse(file, root);

    if(!parsingSuccessful)
        return false;

    width = root["width"].asFloat();
    height = root["height"].asFloat();
    tileWidth = root["tilewidth"].asInt();
    tileHeight = root["tileheight"].asInt();

    for (Json::Value& tileset: root["tilesets"])
        loadTileSet(tileset);

    for(Json::Value& layer: root["layers"])
    {
        if (layer["name"].asString() != "objects")
            loadTileLayer(layer);
        else
            loadObjectLayer(layer);
    }

    return true;
}

std::shared_ptr<Layer> Map::getLayer(const std::string &name)
{
    for (auto& layer: layers)
    {
        if (layer->name == "foreground")
            return layer;
    }

    return std::shared_ptr<Layer>();
}

const std::shared_ptr<std::vector<AnimationFrame>> Map::getAnimation(unsigned int gid)
{
    auto animationIt = animations.find(gid);

    if (animationIt != animations.end())
        return animationIt->second;

    return std::shared_ptr<std::vector<AnimationFrame>>();
}

void Map::setSpriteTextureFromGid(sf::Sprite &sprite, unsigned int gid, int frame)
{
    unsigned int flipFlags = gid >> 29;

    gid &= ~(0b111 << 29);

    auto animationIt = animations.find(gid);

    if (animationIt != animations.end())
    {
        auto& animation = *animationIt->second;

        if(frame >= 0 && frame < (int)animation.size())
            gid = animation[frame].gid;
    }

    auto tileset = *std::find_if(tilesets.rbegin(), tilesets.rend(), [gid](auto ts) { return gid >= ts->firstGid; } );

    int tileid = gid - tileset->firstGid;
    int x = (tileid % tileset->columns) * (tileset->tileWidth + tileset->spacing);
    int y = (tileid / tileset->columns) * (tileset->tileWidth + tileset->spacing);

    int textureRectWidth = tileset->tileWidth;
    int textureRectHeight = tileset->tileHeight;

    if(flipFlags & 2)
    {
        textureRectHeight *= -1;
        y += tileset->tileHeight;
    }

    if(flipFlags & 4)
    {
        textureRectWidth *= -1;
        x += tileset->tileWidth;
    }

    sprite.setTexture(tileset->texture);
    sprite.setTextureRect(sf::IntRect(x, y, textureRectWidth, textureRectHeight));
}

/*const std::vector<std::shared_ptr<AnimationFrame>>& Map::getAnimation(unsigned int gid)
{
    return animations[gid];
}*/

void Map::loadTileSet(Json::Value& tileset)
{
    auto ts = std::make_shared<Tileset>();

    ts->firstGid  = tileset["firstgid"].asUInt();
    ts->columns  = tileset["columns"].asInt();
    ts->imageWidth  = tileset["imagewidth"].asInt();
    ts->imageHeight  = tileset["imageheight"].asInt();
    ts->tileWidth  = tileset["tilewidth"].asInt();
    ts->tileHeight  = tileset["tileheight"].asInt();
    ts->spacing  = tileset["spacing"].asInt();

    ts->texture.loadFromFile("MapData/" + tileset["image"].asString());

    tilesets.push_back(ts);

    for (Json::Value& tile: tileset["tiles"])
    {
        int animationId = ts->firstGid + tile["id"].asInt();

        for (Json::Value& animation: tile["animation"]) {
            unsigned int gid = ts->firstGid + animation["tileid"].asUInt();
            int duration = animation["duration"].asInt();

            if ( animations.find(animationId) == animations.end())
                animations[animationId] = std::make_shared<std::vector<AnimationFrame>>();

            animations[animationId]->push_back(AnimationFrame(gid, duration));
        }
    }
}

void Map::loadTileLayer(Json::Value& layer)
{
    auto tmp = std::make_shared<Layer>(*this);

    tmp->id = layer["id"].asInt();
    tmp->name = layer["name"].asString();
    tmp->visible = layer["visible"].asBool();
    tmp->width = layer["width"].asInt();
    tmp->height = layer["height"].asInt();
    tmp->tilemap = new unsigned int[tmp->width * tmp->height];

    for (size_t i = 0; i < layer["data"].size(); i++)
        tmp->tilemap[i] = layer["data"][(int) i].asUInt();

    layers.push_back(tmp);
}

void Map::loadObjectLayer(Json::Value& layer)
{
    for (Json::Value& object: layer["objects"])
    {
        auto sprite = std::make_shared<Sprite>(*this);

        // Load basic object info
        sprite->id = object["id"].asInt();
        sprite->gid = object["gid"].asUInt();
        sprite->x = object["x"].asInt();
        sprite->y = object["y"].asInt();
        sprite->width = object["width"].asInt();
        sprite->height = object["height"].asInt();
        sprite->y -= sprite->height;

        sprites.push_back(sprite);
    }
}