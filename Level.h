#ifndef LEVEL_H
#define LEVEL_H
#include "Tile.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "ImageManager.h"
#include <iostream>
#include <vector>


class Level
{
    public:
    Level(const std::string& levelPath, const std::string& tilePath, ImageManager& imageManager);
    ~Level(); // Destructor

    private:
    std::vector< std::vector<Tile> > tileMap;
    sf::Vector2i mapSize;   // The size of the map in tiles
};

#endif // LEVEL_H
