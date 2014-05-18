#ifndef TILE_H
#define TILE_H
#include <SFML/Graphics.hpp>


class Tile
{
    friend class Level;

    public:
        enum Type {DIRT,CLEAR,METAL,EXIT,ROCK,DIAMOND};

        Tile(int identifier, int x, int y, const int tileSize);
        Tile(); // Default constructor
        void setTexture(sf::Texture& texture, const int tileSize);
        void setType(Type newType, const int tileSize);
        void draw(sf::RenderWindow& window);
        virtual ~Tile();
    private:
        sf::Sprite sprite;
        Type type;
        //sf::Vector2i gridLocation;
};

#endif // TILE_H
