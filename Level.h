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
    void update(sf::Vector2i playerLocation);
    Tile::Type getTileID(int x, int y);     // Gets the ID of a tile at the specified position
    bool traversable(int x, int y);         // Gets wether or not the specified tile is traversable
    const int getTileSize();

    private:
    struct Obstacle
    {
        int x;
        int y;
        bool falling = false;

        Obstacle(int xLoc, int yLoc)
        {
            x = xLoc;
            y = yLoc;
        }
    };

    Tile** tileMap;
    std::vector<Obstacle> obstacleLocations;
    sf::Vector2i mapSize;   // The size of the map in tiles
    const int tileSize = 64;
    int remainingDiamonds;
    bool exitOpen;
};

#endif // LEVEL_H
