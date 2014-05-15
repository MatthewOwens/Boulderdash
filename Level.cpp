#include "Level.h"
#include <fstream>
#include <sstream>

// Constructor, loads the tilemap and tile identifiers from a specific folder
Level::Level(const std::string& levelPath, const std::string& tilePath, ImageManager& imageManager)
{
    std::string line;
    std::string subString;
    std::ifstream file(levelPath + "map.txt");
    int lineCounter = 0;// Variable to track what line is currently being read

    // Loading the tilesheet associated with the level instance
    imageManager.loadImage(tilePath);

    // Loading the tiles that will populate the level
    while(std::getline(file, line))
    {
        std::stringstream lineStream(line);

        // Determining how many rows are in the level
        if (lineCounter == 0)
        {
            lineStream >> mapSize.x;
            std::cout << "Map is of size: " << mapSize.x;

            // Creating an array of pointers
            tileMap = new Tile*[mapSize.x];
        }
        else if (lineCounter == 1)
        {
            lineStream >> mapSize.y;
            std::cout << "x" << mapSize.y << std::endl;

            // Where an element of type ptr, points to a dynamic array.
            for (int i = 0; i < mapSize.x; i++)
                tileMap[i] = new Tile[mapSize.y];
        }
        else
        {
            int subCounter = 0;
            int result;
            while (std::getline(lineStream, subString, ','))
            {
                // Creating a stringstream to convert the input char to an int
                std::istringstream convert(subString);
                convert >> result;

                // Populating the array
                tileMap[lineCounter - 2][subCounter] = Tile(result, lineCounter-2,subCounter,tileSize);

                // Initilizing the tile's sprite
                tileMap[lineCounter - 2][subCounter].setTexture(imageManager.getTexture(tilePath), tileSize);


                subCounter++;
            }
        }
        lineCounter++;
    }
    std::cout << "\n" << std::endl;

    for(int i = 0; i < mapSize.x; i++)
    {
        for (int j = 0;j < mapSize.y; j++)
            std::cout << tileMap[i][j].type;
        std::cout << "\n";
    }
}

// Draw function
void Level::draw(sf::RenderWindow& window)
{
    for(int i = 0; i < mapSize.x; i++)
    {
        for(int j = 0; j < mapSize.y; j++)
        {
            tileMap[i][j].draw(window);
        }
    }
}

Tile::Type Level::getTileID(int x, int y)
{
    if (x < 0 || x > mapSize.x || y < 0 || y > mapSize.y)
    {
        std::cout << "Requested tile (" << x << "," << y << "is out of the level bounds\n";
        return Tile::DIRT;
    }
    return tileMap[x][y].type;
}

// Level destructor
Level::~Level()
{
    // Cleaning up the dynamically sized arrays
    for(int i = 0; i < mapSize.y; ++i)
        delete [] tileMap[i];

    delete [] tileMap;
}
