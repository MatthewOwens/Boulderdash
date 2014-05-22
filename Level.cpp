#include "Level.h"
#include <fstream>
#include <sstream>

// Constructor, loads the tilemap and tile identifiers from a specific folder
Level::Level(int levelCount, const std::string& tilePath, ImageManager& imageManager)
{
    std::stringstream convert;
    convert << levelCount;
    //remainingDiamonds = 0;
    mapPath = "levels/level" + convert.str() + ".txt";
    std::cout << mapPath << std::endl;
    tilesheetPath = tilePath;
    loadMap(imageManager);
}

// Default constructor, to store the levels in an array
Level::Level(){}

// Load Map function
void Level::loadMap(ImageManager& imageManager)
{
    std::string line;
    std::string subString;
    std::ifstream file(mapPath);
    int lineCounter = 0;// Variable to track what line is currently being read
    exitOpen = false;
    playerCrushed = false;
    cleared = false;
    remainingDiamonds = 0;

    // Loading the tilesheet associated with the level instance
    imageManager.loadImage(tilesheetPath);

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
                if(subString == "s")
                {
                    tileMap[subCounter][lineCounter - 2] = Tile(1,subCounter,lineCounter - 2,tileSize);
                    playerSpawn = sf::Vector2i(subCounter,lineCounter - 2);
                }
                else if (subString == "3")
                {
                    tileMap[subCounter][lineCounter - 2] = Tile(2,subCounter,lineCounter - 2,tileSize);
                    exitLocation = sf::Vector2i(subCounter,lineCounter - 2);
                    std::cout << "Exit Location: " << subCounter << "," << lineCounter - 2 << std::endl;
                }
                else
                    tileMap[subCounter][lineCounter - 2] = Tile(result, subCounter,lineCounter - 2,tileSize);

                // Initilizing the tile's sprite
                tileMap[subCounter][lineCounter - 2].setTexture(imageManager.getTexture(tilesheetPath), tileSize);

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
    diamondCollected = false;

    // Updating the rock & diamond positions
    for(outerItr = obstacleLocations.begin(); outerItr != obstacleLocations.end(); ++outerItr)
    {
        bool moved = false;

        if(tileMap[outerItr->x][outerItr->y + 1].type == Tile::CLEAR)
        {
            outerItr->falling = true;
            tileMap[outerItr->x][outerItr->y + 1].setType(tileMap[outerItr->x][outerItr->y].type, tileSize);
            tileMap[outerItr->x][outerItr->y].setType(Tile::CLEAR, tileSize);
            outerItr->y++;
            moved = true;

        }
        else outerItr->falling = false;

        if(outerItr->x == playerLocation.x && outerItr->y == playerLocation.y
           && outerItr->falling)
        {
            playerCrushed = true;
            std::cout << "SPLAT!" << std::endl;
        }

        if((tileMap[outerItr->x][outerItr->y + 1].type == Tile::ROCK ||
           tileMap[outerItr->x][outerItr->y + 1].type == Tile::DIAMOND)
           && moved == false)
        {
            if (tileMap[outerItr->x + 1][outerItr->y].type == Tile::CLEAR &&
                tileMap[outerItr->x + 1][outerItr->y + 1].type == Tile::CLEAR)
            {
                tileMap[outerItr->x + 1][outerItr->y].setType(tileMap[outerItr->x][outerItr->y].type, tileSize);
                tileMap[outerItr->x][outerItr->y].setType(Tile::CLEAR, tileSize);
                outerItr->x++;
                moved = true;
            }
            else if (tileMap[outerItr->x - 1][outerItr->y].type == Tile::CLEAR &&
                     tileMap[outerItr->x - 1][outerItr->y + 1].type == Tile::CLEAR)
            {
                tileMap[outerItr->x - 1][outerItr->y].setType(tileMap[outerItr->x][outerItr->y].type, tileSize);
                tileMap[outerItr->x][outerItr->y].setType(Tile::CLEAR, tileSize);
                outerItr->x--;
                moved = true;
            }
        }
    }
    // Updating the tiles as the player moves along them
    if(tileMap[playerLocation.x][playerLocation.y].type != Tile::ROCK)
    {
        // If the player collected a diamond
        if(tileMap[playerLocation.x][playerLocation.y].type == Tile::DIAMOND)
        {
            remainingDiamonds--;
            diamondCollected = true;

            // Remove the diamond from the obstacle list
            for(outerItr = obstacleLocations.begin(); outerItr != obstacleLocations.end(); ++outerItr)
            {
                if(playerLocation.x == outerItr->x && playerLocation.y == outerItr->y)
                    break;
            }
            obstacleLocations.erase(outerItr);
        }
        tileMap[playerLocation.x][playerLocation.y].setType(Tile::CLEAR, tileSize);
    }
}

// Draw function
void Level::draw(sf::RenderWindow& window)
{
    for(int i = 0; i < mapSize.x; i++)
    {
        for(int j = 0; j < mapSize.y; j++)
        {
            std::cout << "drawing: " << i << "," << j << "\n";
            tileMap[i][j].draw(window);
        }
    }
}

bool Level::getDiamondCollected()
{
    return diamondCollected;
}

bool Level::isPlayerCrushed()
{
    return playerCrushed;
}

sf::Vector2i Level::getPlayerSpawn()
{
    return playerSpawn;
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
    if (tileMap[x][y].type == Tile::CLEAR ||
        tileMap[x][y].type == Tile::DIRT ||
        tileMap[x][y].type == Tile::DIAMOND||
        (tileMap[x][y].type == Tile::EXIT && exitOpen))
   {
        return true;
   } else return false;
}

std::vector<sf::Vector2i> Level::getObstacleLocations()
{
    std::vector<sf::Vector2i> returns;
    std::vector<Obstacle>::iterator itr;

    for(itr = obstacleLocations.begin(); itr != obstacleLocations.end(); ++itr)
        returns.push_back(sf::Vector2i(itr->x, itr->y));

    return returns;
}

void Level::checkExit(sf::Vector2i playerLocation)
{
    if(remainingDiamonds == 0 && !exitOpen)
    {
        std::cout << "Opening " << exitLocation.x << "," << exitLocation.y << std::endl;
        tileMap[exitLocation.x][exitLocation.y].setType(Tile::EXIT, tileSize);
        exitOpen = true;
    }

    if(playerLocation == exitLocation)
    {
        cleared = true;
    }
}

bool Level::isCleared()
{
    return cleared;
}

const int Level::getTileSize()
{
    return tileSize;
}

sf::Vector2i Level::getMapSize()
{
    return mapSize;
}

int Level::getRemainingDiamonds()
{
    return remainingDiamonds;
}

// Level destructor
Level::~Level()
{
    // Cleaning up the dynamically sized arrays
    for(int i = 0; i < mapSize.y; ++i)
        delete [] tileMap[i];

    delete [] tileMap;
}
