//
// Created by OddMann on 02.11.2018.
//

#ifndef KAPPAPRIDE_MAP_H
#define KAPPAPRIDE_MAP_H

#include <string>
#include <vector>
#include <list>
#include <map>
#include <memory>

#include <SFML/Graphics/Texture.hpp>


namespace sf
{
    class Sprite;
}

namespace Json
{
    class Value;
}

class Object;
class Sprite;
class Layer;

struct Tileset
{

    unsigned int firstGid;
    int columns;
    int imageWidth;
    int imageHeight;
    int tileWidth;
    int tileHeight;
    int spacing;

    sf::Texture texture;
};

struct AnimationFrame
{
    AnimationFrame(unsigned int gid, int duration) : gid(gid), duration(duration) {}

    unsigned int gid;
    int duration;
};

class Map
{

public:

    bool loadFromFile(const std::string& filename);

    int getWidth()      const { return width; }
    int getHeight()     const { return height; }
    int getTileWidth()  const { return tileWidth; }
    int getTileHeight() const { return tileHeight; }

    std::shared_ptr<Layer> getLayer(const std::string& name);

    std::list<std::shared_ptr<Layer>>& getLayers() { return  layers; }

    std::list<std::shared_ptr<Sprite>>& getSprites() { return sprites; }

    void setSpriteTextureFromGid(sf::Sprite& sprite, unsigned int gid, int frame = 0);

    const std::shared_ptr<std::vector<AnimationFrame>> getAnimation(unsigned int gid);



private:

    void loadTileSet(Json::Value& tileset);
    void loadTileLayer(Json::Value& layer);
    void loadObjectLayer(Json::Value& layer);

    float width;
    float height;
    int tileWidth;
    int tileHeight;

    std::list<std::shared_ptr<Tileset>> tilesets;
    std::map<int, std::shared_ptr<std::vector<AnimationFrame>>> animations;

    std::list<std::shared_ptr<Layer>> layers;
    std::list<std::shared_ptr<Sprite>> sprites;
};


#endif //KAPPAPRIDE_MAP_H
