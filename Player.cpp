#include "Player.h"

Player::Player(int gridX, int gridY, const int tileSize, sf::Texture& texture)
    :Entity(gridX, gridY, tileSize, texture)
{
    lives = 3;
}

Player::~Player()
{
    //dtor
}

void Player::decrementLives()
{
    lives--;
}

void Player::update(Level& currentLevel, InputManager& inputManager)
{
    if(inputManager.pressedOnce("up") &&
       currentLevel.traversable(gridLocation.x, gridLocation.y - 1))
        gridLocation.y--;
    else if (inputManager.pressedOnce("down") &&
             currentLevel.traversable(gridLocation.x, gridLocation.y + 1))
        gridLocation.y++;
    else if (inputManager.pressedOnce("right") &&
             currentLevel.traversable(gridLocation.x + 1, gridLocation.y))
        gridLocation.x++;
    else if (inputManager.pressedOnce("left") &&
             currentLevel.traversable(gridLocation.x - 1, gridLocation.y))
        gridLocation.x--;

    sprite.setPosition(gridLocation.x * currentLevel.getTileSize(), gridLocation.y * currentLevel.getTileSize());
}

bool Player::deathCheck(std::vector<sf::Vector2i> obstacleLocations)
{
    std::vector<sf::Vector2i>::iterator itr;
    for(itr = obstacleLocations.begin(); itr != obstacleLocations.end(); ++itr)
    {
        if(itr->x == gridLocation.x && itr->y == gridLocation.y)
            return true;
    }
    return false;
}
