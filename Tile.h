#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>


class Tile
{
    public:
        enum Type {DIRT,CLEAR,METAL,ROCK,DIAMOND};

        Tile(int gridX, int gridY, int identifier);
        void setTexture(sf::Texture& texture, const int tileSize);
        void setType(int newType);
        virtual ~Tile();
    private:
        sf::Sprite sprite;
        Type type;
        sf::Vector2i gridLocation;
};

#endif // TILE_H
