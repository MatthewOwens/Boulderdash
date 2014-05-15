#ifndef LEVEL_H
#define LEVEL_H
#include "Tile.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "ImageManager.h"
#include <iostream>


class Level
{
    public:
    Level(const std::string& levelPath, const std::string& tilePath, ImageManager& imageManager);
    ~Level(); // Destructor
    void draw(sf::RenderWindow& window);
    Tile::Type getTileID(int x, int y);   // Gets the ID of a tile at the specified position

    private:
    Tile** tileMap;
    sf::Vector2i mapSize;   // The size of the map in tiles
    const int tileSize = 64;
};

#endif // LEVEL_H
