#include "Camera2D.h"
#include <sstream>
#include <fstream>

// Default constructor, sets the camera according to the resolution
// and defines the camera's movement limits
Camera2D::Camera2D(int resW, int resH, int mapW, int mapH, int tileSize)
{
    camera.reset(sf::FloatRect(0, 0, resW, resH));
    mapBounds = sf::IntRect(0, 0, mapW * tileSize, mapH * tileSize);
    panComplete = false;
}

// Sets the position of the camera
void Camera2D::setCenter(int x, int y)
{
    camera.setCenter(x,y);
}

// Move the camera by an offset
void Camera2D::move(int offsetX, int offsetY)
{
    camera.move(offsetX, offsetY);
}

// Loads the locations within the level that the camera should pan through once
// the level has been loaded.
void Camera2D::loadPanPoints(const std::string& folderPath, int tileSize)
{
    // Clearing the previously stored pan points
    panPoints.clear();
    panComplete = false;
    previousPanPoint = panPoints.begin();

    // Opening the target file
    std::ifstream file(folderPath + "/camera.txt");
    std::string line;
    sf::Vector2i point;

    // While there are lines to get
    while(std::getline(file,line))
    {
        std::string substring;
        std::istringstream ss(line);

        std::getline(ss, substring, ',');
        std::istringstream intConvert(substring);
        intConvert >> point.x;

        std::getline(ss, substring, ',');
        intConvert.str(substring);
        intConvert >> point.y;

        std::cout << "Loaded pan point (" << point.x << "," << point.y << ")";
        std::cout << std::endl;
    }
}

// Moves the camera towards the pan points if needed
void Camera2D::pan()
{
    // If the camera hasn't panned over the level yet
    if (!panComplete)
    {
        // Checking if the camera should stop panning over the level
        if (previousPanPoint == panPoints.end() - 1)
        {
            std::cout << "Camera Pan Complete" << std::endl;
            panComplete = true;
            return;
        }
        else
        {
            sf::Vector2i diff()
        }
    }
}


Camera2D::~Camera2D()
{
    //dtor
}
