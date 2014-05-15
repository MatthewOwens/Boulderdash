#include "Obstacle.h"
#include "Tile.h"

Obstacle::Obstacle(int x, int y, sf::Texture& texture)
    : Entity(x, y, texture)
{
    //ctor
}

Obstacle::~Obstacle()
{
    //dtor
}

void Obstacle::update(sf::Vector2i playerLocation, sf::Vector2i playerPreviousLocation, Level& currentLevel)
{
    // Checking if this obstacle is falling
    if(currentLevel.getTileID(gridLocation.x, gridLocation.y + 1) == Tile::CLEAR)
        gridLocation.y++;

}
