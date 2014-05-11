// The Camera2D class builds upon SFML's 2D camera class, View
// This class adds the ability to stop the camera panning at the edge of the
// levels and lets the camera pan over important parts of the level at the start

#ifndef CAMERA2D_H
#define CAMERA2D_H


class Camera2D
{
    public:
        Camera2D(int resW, int resH, int mapW, int mapH, int tileSize);
        virtual ~Camera2D();
        void setCenter(int x, int y);
        void move(int offsetX, int offsetY);
        void loadPanPoints(const std::string& folderPath);
        void pan();
    private:
        std::list<sf::Vector2i> panPoints;
        std::list<sf::Vector2i>::iterator previousPanPoint;
        bool panComplete;
        sf::IntRect mapBounds;
        sf::View camera;
};

#endif // CAMERA2D_H
