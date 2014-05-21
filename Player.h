#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "InputManager.h"
#include "Level.h"


class Player : public Entity
{
    public:
        Player(int gridX, int gridY, const int tileSize, sf::Texture& texture);
        virtual ~Player();
        void update(Level& currentLevel, InputManager& inputManager);
        void decrementLives();
        bool deathCheck(std::vector<sf::Vector2i> obstacleLocations);
    private:
        int lives;

};

#endif // PLAYER_H
