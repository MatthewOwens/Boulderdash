#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "Entity.h"
#include "Level.h"


class Obstacle : public Entity
{
    public:
        Obstacle(int x, int y, sf::Texture& texture);
        virtual ~Obstacle();
        void update(sf::Vector2i playerLocation, sf::Vector2i playerPreviousLocation, Level& currentLevel);
    private:
        bool isDiamond;
};

#endif // OBSTACLE_H
