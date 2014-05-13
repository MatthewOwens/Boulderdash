/// The level class is used to define a level within the game.
/// This class contains instances of the Tile, Guard and Item classes
/// and takes information from the Player class to pass through into the other
/// classes.

#ifndef LEVEL_H
#define LEVEL_H
#include "Tile.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include "ImageManager.h"
#include "Player.h"
#include <iostream>
#include <list>


class Level
{
    typedef Tile (*TilePtr)[10];

    public:
        Level(const std::string& filepath, ImageManager &imageManager);
        virtual ~Level();
        void draw(sf::RenderWindow& window);
        //void update(std::list<sf::Vector2i> p_visibleTiles, sf::FloatRect p_bounds, sf::FloatRect p_weaponBounds, bool p_attacking);
        //void reset();

        // Accessor methods
        TilePtr getTiles();
        Tile getTile(int x, int y);
        sf::Vector2i getSpawn();
        const int getTileSize();

    private:
        Tile tiles[10][10];         // The tiles that will make the level map
        std::list<Item> items;      // The items that will populate the level
        std::list<Guard> guards;    // THe guards that will populate the level
        sf::Vector2i playerSpawn;   // The player's spawn location on this level
        const int tileSize = 64;
        bool levelComplete = false; // Whether or not the level is done.


        // Private methods
        void loadMap(const std::string& filepath, ImageManager &imageManager);
};

#endif // LEVEL_H
