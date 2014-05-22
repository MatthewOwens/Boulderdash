#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "InputManager.h"
#include "Level.h"


class Player : public Entity
{
    public:
        Player(int gridX, int gridY, int tileSize, sf::Texture& texture);
        virtual ~Player();
        void update(Level& currentLevel, InputManager& inputManager);
        void decrementLives();
        int getRemainingLives();
    private:
        int lives;

};

#endif // PLAYER_H
