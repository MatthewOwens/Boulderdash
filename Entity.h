// Entity is an abstract class that acts as a base for the Player, Obstacle
// and Enemy classes.

#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>


class Entity
{
    public:
        Entity(int gridX, int gridY);
        Entity(int gridX, int gridY, sf::Texture& texture);
        void initAnimations(int animLength, int frameLength);
        void gridMove(int offsetX, int offsetY);
        sf::Vector2i getGridLocation();
        void setGridLocation(int gridX, int gridY);
        void setTexture(sf::Texture& texture);
        void setCurrentAnimation(int newAnim);
        virtual bool update();
        void draw(sf::RenderWindow& window);
        virtual ~Entity() = 0;  // Making the class abstract

    protected:
        sf::Vector2i gridLocation;  // The entity's location on the grid
        sf::Sprite sprite;          // The sprite assocaited with the entity
        bool exists;                // Wether or not the entity currently 'exists' in the game world

        int currentAnimFrame;       // The sprite's current frame of animation, defaults to zero
        int maxAnimFrames;          // The maximum number of frames for this sprite's animatinos
        int animFrameTime;          // How long each frame of the animation will be displayed for (in milliseconds)
        int currentAnimation;       // The current animation that is being played
        sf::Clock animClock;        // Clock to track the timing between animation frames
        sf::IntRect sourceRect;     // The section of the sprite to draw
};
#endif // ENTITY_H
