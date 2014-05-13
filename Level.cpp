#include "Level.h"
#include <fstream>
#include <sstream>

// Constructor, ImageManager is not const as it needs to be manipulated
Level::Level(const std::string& filepath, ImageManager &imageManager)
{
    // Loading this level's tilesheet
    imageManager.loadImage(filepath + "/tilesheet.png");

    // Loading the map
    loadMap(filepath, imageManager);
}

// Loading the tiles, this method is called in the constructor
void Level::loadMap(const std::string& filepath, ImageManager &imageManager)
{
    std::ifstream file;
    int counter = 0;    // Used for navigating the file
    std::string line;

    // Opening the map file
    file.open(filepath + "/map.txt");

    // Ensuring that the map file was opened correctly
    if (file.good())
    {
        // Parsing the map file
        while(std::getline(file, line))
        {
            for (int i = 0; i < 10; i++)
            {
                if(line[i] != 's')
                    tiles[i][counter] = Tile(imageManager.getImage(filepath + "/tilesheet.png"),
                                             tileSize, line[i] - '0', i, counter);
                else
                {
                    tiles[i][counter] = Tile(imageManager.getImage(filepath + "/tilesheet.png"),
                                            tileSize, 0, i, counter);
                    playerSpawn = sf::Vector2i(i * tileSize, counter * tileSize);
                }
                //std::cout << line[i];
            }
            counter++;
            //std::cout << std::endl;
        }
    }
    else    // You done goofed.
    {
        std::cout << "Map file at '" << filepath << "/map.txt' was not found!" << std::endl;
    }
    // Closing the map file
    file.close();
}


// Draw method, takes a const reference to the window
void Level::draw(sf::RenderWindow& window)
{
    std::list<Item>::iterator itr_item;
    // Drawing the tiles
    for(int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            window.draw(tiles[i][j].sprite);
        }
    }
}


Level::~Level()
{
    //dtor
}

// Accessor methods
Level::TilePtr Level::getTiles()
{
    return tiles;
}
Tile Level::getTile(int x, int y) { return tiles[x][y]; }
sf::Vector2i Level::getSpawn() { return playerSpawn; }
const int Level::getTileSize() { return tileSize; }
