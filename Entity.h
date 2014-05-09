#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>


class Entity
{
    public:
        Entity(int gridX, int gridY);
        Entity(int gridX, int gridY, sf::Texture& texture);
        void initAnimations(int animLength);
        void gridMove(int offsetX, int offsetY);
        sf::Vector2i getGridLocation();
        void setGridLocation(int gridX, int gridY);
        void setTexture(sf::Texture& texture);
        void setCurrentAnimation(int newAnim);
        void draw(sf::RenderWindow& window);
        virtual ~Entity();

    protected:
        sf::Vector2i gridLocation;  // The entity's location on the grid
        sf::Sprite sprite;          // The sprite assocaited with the entity
        bool exists;                // Wether or not the entity currently 'exists' in the game world

        int currentAnimFrame;       // The sprite's current frame of animation, defaults to zero
};
#endif // ENTITY_H
