#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>


class Tile
{
    friend class Level;

    public:
        enum Type {DIRT,CLEAR,METAL,EXIT,ROCK,DIAMOND};

        Tile(int identifier, int x, int y, int tileSize);
        Tile(); // Default constructor
        void setTexture(sf::Texture& texture, int tileSize);
        void setType(Type newType, int tileSize);
        void draw(sf::RenderWindow& window);
        virtual ~Tile();
    private:
        sf::Sprite sprite;
        Type type;
        sf::Vector2i gridLocation;
};

#endif // TILE_H
