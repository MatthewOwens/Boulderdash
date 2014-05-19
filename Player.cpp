#include "Player.h"

Player::Player(int gridX, int gridY, sf::Texture& texture)
    :Entity(gridX, gridY, texture)
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
       currentLevel.traversable(gridLocation.x, gridLocation.y + 1))
        gridLocation.y++;
    else if (inputManager.pressedOnce("down") &&
             currentLevel.traversable(gridLocation.x, gridLocation.y - 1))
        gridLocation.y--;
    else if (inputManager.pressedOnce("right") &&
             currentLevel.traversable(gridLocation.x + 1, gridLocation.y))
        gridLocation.x++;
    else if (inputManager.pressedOnce("left") &&
             currentLevel.traversable(gridLocation.x - 1, gridLocation.y))
        gridLocation.x--;

    sprite.setPosition(gridLocation.x * currentLevel.getTileSize(), gridLocation.y * currentLevel.getTileSize());
    std::cout << sprite.getPosition().x << " " << sprite.getPosition().y << std::endl;
    std::cout << gridLocation.x << " " << gridLocation.y << std::endl;
}
