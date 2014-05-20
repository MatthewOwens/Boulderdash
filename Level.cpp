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
    exitOpen = false;

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

            // Creating an array of pointers
            tileMap = new Tile*[mapSize.x];
        }
        else if (lineCounter == 1)
        {
            lineStream >> mapSize.y;

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
                tileMap[subCounter][lineCounter - 2] = Tile(result, subCounter,lineCounter - 2,tileSize);

                // Initilizing the tile's sprite
                tileMap[subCounter][lineCounter - 2].setTexture(imageManager.getTexture(tilePath), tileSize);

                // Incrementing the counters
                if (result == 5)
                {
                    remainingDiamonds++;
                    obstacleLocations.insert(obstacleLocations.begin(),Obstacle(subCounter, lineCounter - 2));
                }
                else if (result == 4)
                    obstacleLocations.insert(obstacleLocations.begin(),Obstacle(subCounter, lineCounter - 2));

                subCounter++;
            }
        }
        lineCounter++;
    }
}

// Update Method
void Level::update(sf::Vector2i playerLocation)
{
    std::vector<Obstacle>::iterator outerItr;
    std::vector<Obstacle>::iterator innerItr;

    // Updating the rock & diamond positions
    for(outerItr = obstacleLocations.begin(); outerItr != obstacleLocations.end(); ++outerItr)
    {
        bool moved = false;
        // Checking if the obstacle can fall
        if(tileMap[outerItr->x][outerItr->y + 1].type == Tile::CLEAR)
        {
            std::cout << "Changing " << tileMap[outerItr->x][outerItr->y + 1].type
            << " to " << tileMap[outerItr->x][outerItr->y].type << "\n";

            tileMap[outerItr->x][outerItr->y + 1].setType(tileMap[outerItr->x][outerItr->y].type, tileSize);
            tileMap[outerItr->x][outerItr->y].setType(Tile::CLEAR, tileSize);
            outerItr->y++;
            moved = true;
            outerItr->falling = true;
        }
        if(!moved && outerItr->falling) // Making obstacles roll off each other
        {
            for(innerItr = obstacleLocations.begin(); innerItr != obstacleLocations.end();
            ++innerItr)
            {
                if(outerItr->x == innerItr->x && outerItr->y + 1== innerItr->y)
                {
                    if(tileMap[outerItr->x+1][outerItr->y].type == Tile::CLEAR)
                    {
                        tileMap[outerItr->x + 1][outerItr->y].setType(tileMap[outerItr->x][outerItr->y].type, tileSize);
                        tileMap[outerItr->x][outerItr->y].setType(Tile::CLEAR, tileSize);
                        outerItr->x++;
                        outerItr->falling = false;
                    }
                    else if (tileMap[outerItr->x-1][outerItr->y].type == Tile::CLEAR)
                    {
                        tileMap[outerItr->x - 1][outerItr->y].setType(tileMap[outerItr->x][outerItr->y].type, tileSize);
                        tileMap[outerItr->x][outerItr->y].setType(Tile::CLEAR, tileSize);
                        outerItr->x--;
                        outerItr->falling = false;
                    }
                }
            }
        }
    }

    // Updating the tiles as the player moves along them
    if(tileMap[playerLocation.x][playerLocation.y].type == Tile::DIAMOND)
        remainingDiamonds--;

    tileMap[playerLocation.x][playerLocation.y].setType(Tile::CLEAR, tileSize);
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

bool Level::traversable(int x, int y)
{
    if(tileMap[x][y].type == Tile::CLEAR ||
       tileMap[x][y].type == Tile::DIRT ||
       tileMap[x][y].type == Tile::DIAMOND ||
      (tileMap[x][y].type == Tile::EXIT && exitOpen))
   {
        return true;
   } else return false;
}

const int Level::getTileSize()
{
    return tileSize;
}

// Level destructor
Level::~Level()
{
    // Cleaning up the dynamically sized arrays
    for(int i = 0; i < mapSize.y; ++i)
        delete [] tileMap[i];

    delete [] tileMap;
}
