#ifndef USERINTERFACE_H
#define USERINTERFACE_H
#include <map>
#include "InterfaceElement.h"
#include "ImageManager.h"


class UserInterface
{
    public:
        enum Screen {TITLE,PLAY,GAMEOVER,WIN};
        UserInterface(int resX, int resY, ImageManager& imageManager);
        virtual ~UserInterface();
        void initInterface(Screen newScreen, ImageManager& imageManager);
        void updatePlay(sf::Vector2i playerPosition, const int tileSize, int remainingLives, int remainingDiamonds);
        int updateTitle(sf::RenderWindow& window);
        void drawAbsolute(sf::RenderWindow& window);
        void drawRelative(sf::RenderWindow& window);
        void updateLives(sf::Vector2i playerSpawn, const int tileSize);
        void updateDiamonds(sf::Vector2i playerSpawn, const int tileSize);
        Screen getScreenState();
    private:
        std::map<std::string, InterfaceElement> elements;
        sf::Font font;
        sf::Vector2i resolution;
        sf::Sprite backgroundSprite;
        Screen screenState;
        bool livesUpdate;
        bool diamondsUpdate;
};

#endif // USERINTERFACE_H
