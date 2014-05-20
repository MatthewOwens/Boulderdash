// The Camera2D class builds upon SFML's 2D camera class, View
// This class adds the ability to stop the camera panning at the edge of the
// levels and lets the camera pan over important parts of the level at the start

#ifndef CAMERA2D_H
#define CAMERA2D_H
#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>

class Camera2D
{
    public:
        Camera2D(int resW, int resH, int mapW, int mapH, int tileSize);
        virtual ~Camera2D();
        void setCenter(int x, int y);
        void move(int offsetX, int offsetY);
        void loadPanPoints(const std::string& folderPath, int tileSize);
        void pan();
        void update(sf::Vector2i playerLocation, const int tileSize);
        sf::View& getView();
    private:
        std::list<sf::Vector2i> panPoints;
        std::list<sf::Vector2i>::iterator previousPanPoint;
        bool panComplete;
        sf::IntRect mapBounds;
        sf::IntRect viewBounds;
        sf::View camera;
};

#endif // CAMERA2D_H
