#include "Entity.h"

// Entity Constructor, only sets the entity's grid location
Entity::Entity(int gridX, int gridY)
{
    gridLocation = sf::Vector2i(gridX, gridY);
}

// Alternate Constructor, sets the grid location and the sprite texture
Entity::Entity(int gridX, int gridY, sf::Texture& texture)
{
    gridLocation = sf::Vector2i(gridX, gridY);
    sprite.setTexture(texture);
}

// Animation initilisation, sets the length of the entity's animations
// in frames. As well as the framerate those animations should be played at.
// This is seperate from the constructor so that animations do not have to be
// implimented prior to testing the entity.
void Entity::initAnimations(int animLength, int frames)
{
    maxAnimLength = animLength;
    animFramerate = frames;
}

// Move the entity by an offset, prevents calling a getter and setter
// each time the entity moves.
void Entity::gridMove(int offsetX, int offsetY)
{
    gridLocation.x += offsetX;
    gridLocation.y += offsetY;
}

// Used to move the entity to an absolute position on the grid without
// creating a new entity, generally used when transistioning between levels
void Entity::setGridLocation(int gridX, int gridY)
{
    gridLocation = sf::Vector2i(gridX, gridY);
}

// Used to change the animation that is being displayed.
// Will also reset the current animation frame to zero.
void Entity::setCurrentAnimation(int newAnim)
{
    currentAnimation = newAnim;
    currentAnimFrame = 0;
}

// Used to draw the entity
void Entity::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
}

Entity::~Entity()
{
    //dtor
}
