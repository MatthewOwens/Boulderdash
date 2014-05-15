#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>


class Tile
{
    friend class Level;

    public:
        enum Type {DIRT,CLEAR,METAL,ROCK,DIAMOND};

        Tile(int identifier);
        Tile(); // Default constructor
        void setTexture(sf::Texture& texture, const int tileSize);
        void setType(int newType);
        virtual ~Tile();
    private:
        sf::Sprite sprite;
        Type type;
        //sf::Vector2i gridLocation;
};

#endif // TILE_H
