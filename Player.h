#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"


class Player : public Entity
{
    public:
        Player(int gridX, int gridY, sf::Texture& texture);
        virtual ~Player();
    protected:
    private:
};

#endif // PLAYER_H
