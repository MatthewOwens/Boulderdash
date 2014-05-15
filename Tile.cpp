#include "Tile.h"
#include <iostream>

Tile::Tile(int identifier)
{
    //gridLocation = sf::Vector2i(gridX, gridY);

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
    default:
        std::cout << "Tile type: " << identifier << " is invalid, defaulting to 0 (DIRT)" << std::endl;
        type = Type::DIRT;
        break;
    }
}

// Default constructor
Tile::Tile(){}

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
    default:
        type = Type::DIRT;
        break;
    }
}

Tile::~Tile()
{
    //dtor
}
