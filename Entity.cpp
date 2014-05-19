#include "Entity.h"
#include <iostream>

// Entity Constructor, only sets the entity's grid location
Entity::Entity(int gridX, int gridY)
{
    gridLocation = sf::Vector2i(gridX, gridY);
    sprite.setPosition(gridX, gridY);
    currentAnimation = 0;
    currentAnimFrame = 0;
}

// Alternate Constructor, sets the grid location and the sprite texture
Entity::Entity(int gridX, int gridY, sf::Texture& texture)
{
    gridLocation = sf::Vector2i(gridX, gridY);
    sprite.setPosition(gridX, gridY);
    sprite.setTexture(texture);
    currentAnimation = 0;
    currentAnimFrame = 0;
}

// Animation initilisation, sets the length of the entity's animations
// in milliseconds. As well as the framerate those animations should be played at.
// This is seperate from the constructor so that animations do not have to be
// implimented prior to testing the entity.
void Entity::initAnimations(int animLength, int frameLength)
{
    sourceRect = sf::IntRect(0,0,64,64);
    maxAnimFrames = animLength;
    animFrameTime = frameLength;
    sprite.setTextureRect(sourceRect);

    std::cout << "Sprite Bounds:" << std::endl;
    std::cout << "X: " << sprite.getGlobalBounds().left << std::endl;
    std::cout << "Y: " << sprite.getGlobalBounds().top << std::endl;
    std::cout << "W: " << sprite.getGlobalBounds().width << std::endl;
    std::cout << "H: " << sprite.getGlobalBounds().height << std::endl;
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

bool Entity::update()
{
    //std::cout << animClock.getElapsedTime().asMilliseconds() << std::endl;

    // If the established frame time has elapsed
    if (animClock.getElapsedTime().asMilliseconds() >= animFrameTime)
    {
        currentAnimFrame++;
        animClock.restart();

        if (currentAnimFrame == maxAnimFrames)
            currentAnimFrame = 0;

        // Updating the source rectangle
        sourceRect = sf::IntRect(currentAnimFrame * 64, currentAnimation * 64, 64, 64);
        sprite.setTextureRect(sourceRect);
    }
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
