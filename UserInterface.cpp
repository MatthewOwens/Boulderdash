#include "UserInterface.h"
#include <iostream>
#include <sstream>

UserInterface::UserInterface(int resX, int resY, ImageManager& imageManager)
{
    font.loadFromFile("assets/fonts/04B_30.TTF");
    resolution = sf::Vector2i(resX, resY);
    livesUpdate = false;
    diamondsUpdate = false;
    initInterface(Screen::TITLE, imageManager);
}

UserInterface::~UserInterface()
{
    //dtor
}

void UserInterface::initInterface(Screen newScreen, ImageManager& imageManager)
{
    // Clearing the previous UI elements
    elements.clear();

    // Updating the screenstate
    screenState = newScreen;

    // Populating the screen based on the input
    switch(newScreen)
    {
    case Screen::TITLE:
        elements["exitButton"] = InterfaceElement(resolution.x - 150, resolution.y - 50,"exit",font,10,10);
        elements["exitButton"].sprite.setTexture(imageManager.getTexture("button"));

        elements["startButton"] = InterfaceElement(50,resolution.y - 50,"start",font,10,10);
        elements["startButton"].sprite.setTexture(imageManager.getTexture("button"));

        elements["titleText"] = InterfaceElement(resolution.x / 2 - 150, 50, "BoulderDash",font,0,0);
        backgroundSprite.setTexture(imageManager.getTexture("titleBG"));
        break;

    case Screen::PLAY:
        elements["livesText"] = InterfaceElement(0,0,"",font,64,0,true);
        elements["livesText"].headerText.setColor(sf::Color::Transparent);

        elements["diamondsText"] = InterfaceElement(0,0,"",font,64,0,true);
        elements["diamondsText"].headerText.setColor(sf::Color::Transparent);
        backgroundSprite.setTexture(sf::Texture());
        break;

    case Screen::GAMEOVER:
        elements["endText"] = InterfaceElement(resolution.x / 2 - 150, 50, "Game Over",font,0,0);
        backgroundSprite.setTexture(imageManager.getTexture("endBG"));
        break;

    case Screen::WIN:
        elements["winText"] = InterfaceElement(resolution.x / 2 - 150, 50, "Congratulations!",font,0,0);
        elements["winText"].headerText.setColor(sf::Color::Green);
        backgroundSprite.setTexture(imageManager.getTexture("titleBG"));
    }
}

void UserInterface::updatePlay(sf::Vector2i playerPosition, const int tileSize, int remainingLives, int remainingDiamonds)
{
    int livesY = elements["livesText"].headerText.getPosition().y;
    int diamondsY = elements["diamondsText"].headerText.getPosition().y;
    std::stringstream convert;

    if(livesUpdate)
    {
        convert << remainingLives;
        elements["livesText"].headerText.setString(convert.str() + " lives remaining.");
        livesY--;
        elements["livesText"].headerText.setPosition(playerPosition.x * tileSize + 128, livesY);
        elements["livesText"].headerText.setColor(sf::Color(227,127,127));

        if(playerPosition.y * tileSize - livesY >= 30)
            livesUpdate = false;
    }
    else
    {
        elements["livesText"].headerText.setColor(sf::Color::Transparent);
    }
    if (diamondsUpdate)
    {
        printf("DIAMOND UPDATTU\n");
        convert << remainingDiamonds;
        diamondsY--;
        elements["diamondsText"].headerText.setString(convert.str() + " diamonds remaining.");
        elements["diamondsText"].headerText.setPosition(playerPosition.x * tileSize + 128, diamondsY);
        elements["diamondsText"].headerText.setColor(sf::Color::Cyan);

        if(playerPosition.y * tileSize - diamondsY >= 30)
            diamondsUpdate = false;
    }
    else
    {
        elements["diamondsText"].headerText.setColor(sf::Color::Transparent);
    }
}

int UserInterface::updateTitle(sf::RenderWindow& window)
{
    int val = 0;
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        printf("click\n");
        int mouseX = sf::Mouse::getPosition(window).x;
        int mouseY = sf::Mouse::getPosition(window).y;

        if(elements["startButton"].sprite.getGlobalBounds().contains(mouseX, mouseY))
            val = 1;
        if(elements["exitButton"].sprite.getGlobalBounds().contains(mouseX, mouseY))
            val = 2;
    }
    return val;
}

void UserInterface::updateLives(sf::Vector2i playerSpawn, const int tileSize)
{
    livesUpdate = true;
    elements["livesText"].headerText.setPosition(playerSpawn.x * tileSize, playerSpawn.y * tileSize);
}

void UserInterface::updateDiamonds(sf::Vector2i playerSpawn, const int tileSize)
{
    printf("DIAMOND GETTU\n");
    diamondsUpdate = true;
    elements["diamondsText"].headerText.setPosition(playerSpawn.x * tileSize, playerSpawn.y * tileSize);
}

void UserInterface::drawAbsolute(sf::RenderWindow& window)
{
    std::map<std::string, InterfaceElement>::iterator itr;
    if(screenState != Screen::PLAY)
        window.draw(backgroundSprite);

    for(itr = elements.begin(); itr != elements.end(); ++itr)
    {
        if(!itr->second.cameraRelative)
            itr->second.draw(window);
    }
}

void UserInterface::drawRelative(sf::RenderWindow& window)
{
    std::map<std::string, InterfaceElement>::iterator itr;

    for(itr = elements.begin(); itr != elements.end(); ++itr)
    {
        if(itr->second.cameraRelative)
            itr->second.draw(window);
    }
}

UserInterface::Screen UserInterface::getScreenState()
{
    return screenState;
}
