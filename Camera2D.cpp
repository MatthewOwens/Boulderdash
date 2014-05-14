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
    previousPanPoint = panPoints.end();

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
        std::list<sf::Vector2i>::iterator tempItr;
        tempItr = panPoints.end();
        tempItr--;

        // Checking if the camera should stop panning over the level
        if (previousPanPoint == tempItr)
        {
            std::cout << "Camera Pan Complete" << std::endl;
            panComplete = true;
            return;
        }
        else
        {
            // If the camera hasn't started panning yet, move it to the first
            // location.
            if (previousPanPoint == panPoints.end())
            {
                previousPanPoint = panPoints.begin();
                setCenter(previousPanPoint->x, previousPanPoint->y);
                return;

            }

            // Finding the difference between the camera's current location and
            // the next location.
            previousPanPoint++;

            sf::Vector2i diff((previousPanPoint)->x - camera.getCenter().x,
                              (previousPanPoint)->y - camera.getCenter().y);

            // The difference is zero, keep the previous pan point incrimented
            // (so it now represents the camera location) and leave the method
            // The camera movement is dropped for this update but at ~60
            // updates per second this becomes negligable.
            if(diff.x == 0 && diff.y == 0)
                return;

            previousPanPoint--;

            // Moving the camera along the X axis
            if(diff.x > 0)
                camera.move(1,0);
            else if (diff.x < 0)
                camera.move(-1,0);

            // Moving the camera along the Y axis
            if(diff.y > 0)
                camera.move(0,1);
            else if (diff.y < 0)
                camera.move(0,-1);
        }
    }
}

void Camera2D::update(sf::Vector2f playerLocation)
{
    // Don't update the camera if it is still panning.
    if(!panComplete)
        return;

    // Getting the viewport
    const sf::FloatRect viewport = camera.getViewport();

    // Centering the camera on the player's location
    camera.setCenter(playerLocation);

    // Moving the camera if it goes past the edges of the map
    if(viewport.left < mapBounds.left)
        camera.move(-viewport.left,0);

    if(viewport.left + viewport.width >
       mapBounds.left + mapBounds.width)
    {
        camera.move((mapBounds.left + mapBounds.width) - (viewport.left + viewport.width),0);
    }

    if(viewport.top < mapBounds.top)
        camera.move(0, -viewport.top);

    if(viewport.top + viewport.height >
       mapBounds.height + mapBounds.width)
    {
        camera.move(0,(mapBounds.top + mapBounds.height) - (viewport.top + viewport.height));
    }
}

Camera2D::~Camera2D()
{
    //dtor
}
