#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H
#include <SFML/Graphics.hpp>
#include <map>

class ImageManager
{
    public:
        ImageManager();
        virtual ~ImageManager();
        void loadImage(const std::string& filePath);
        void loadImage(const std::string& filePath, const std::string& key);
        void unloadImage(const std::string& key);
        sf::Texture& getTexture(const std::string& key);
    private:
        std::map<std::string, sf::Texture> textures;
};

#endif // IMAGEMANAGER_H
