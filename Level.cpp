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

    std::vector< std::vector<Tile> >::iterator outerItr = tileMap.begin();

    // Loading the tilesheet associated with the level instance
    //imageManager.loadImage(tilePath);

    // Loading the tiles that will populate the level
    while(std::getline(file, line))
    {
        std::stringstream lineStream(line);

        // Determining how many rows are in the level
        if (lineCounter == 0)
        {
            lineStream >> mapSize.x;
            std::cout << "Map is of size: " << mapSize.x;
        }
        else if (lineCounter == 1)
        {
            lineStream >> mapSize.y;
            std::cout << "x" << mapSize.y << std::endl;
        }
        else
        {
            std::string subStr;
            std::vector<Tile> inner;

            while (std::getline(lineStream, subStr, ','))
            {
                std::stringstream intConvert(subStr);
                int tileID;

                intConvert >> tileID;
                Tile tempTile(tileID);
                inner.push_back(tempTile);
            }
            std::cout << inner.size();
            tileMap.push_back(inner);

        }
        //std::advance(outerItr, 1);
        if (lineCounter > 1)
        {
            //std::cout << outerItr->size() << std::endl;
            //std::advance(outerItr,1);
        }
        lineCounter++;
    }
}

// Level destructor
Level::~Level()
{

}
