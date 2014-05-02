#include "Tile.h"

Tile::Tile(int gridX, int gridY, int identifier)
{
    gridLocation = sf::Vector2i(gridX, gridY);

    // Determining the type of tile specified
    switch(identifier)
    {
    case 0:
        type = Type::DIRT;
        break;
    case 1:
        type = Type::CLEAR;
        break;
    case 2:
        type = Type::METAL;
        break;
    case 3:
        type = Type::ROCK;
        break;
    case 4:
        type = Type::DIAMOND;
        break;
    default:
        type = Type::ROCK;
        break;
    }
}

void Tile::setTexture(sf::Texture& texture, const int tileSize)
{
    // Associating a texture (tileSheet) with this sprite
    sprite.setTexture(texture);

    // Determining what part of the tileSheet to draw
    sprite.setTextureRect( sf::IntRect(type * tileSize, type * tileSize, tileSize, tileSize) );
}

void Tile::setType(int newType)
{
    switch(newType)
    {
    case 0:
        type = Type::DIRT;
        break;
    case 1:
        type = Type::CLEAR;
        break;
    case 2:
        type = Type::METAL;
        break;
    case 3:
        type = Type::ROCK;
        break;
    case 4:
        type = Type::DIAMOND;
        break;
    default:
        type = Type::ROCK;
        break;
    }
}

Tile::~Tile()
{
    //dtor
}
