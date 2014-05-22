#include <iostream>
#include <SFML/Graphics.hpp>
#include "ImageManager.h"
#include "Level.h"
#include "Camera2D.h"
#include "InputManager.h"
#include "Player.h"
#include "UserInterface.h"

int main()
{
    // initializing the SFML Window
    sf::RenderWindow window(sf::VideoMode(1280,720), "Boulderdash");
    window.setFramerateLimit(60);

    // initializing the manager classes
    ImageManager imageManager;
    InputManager inputManager;

    // initializing the UI
    UserInterface ui(1280,720,imageManager);

    // initializing the level & level counter
    int levelCount = 0;
    Level levels[4];

    for(int i = 0; i < 4; i++)
        levels[i] = Level(levelCount, "assets/tilesheets/upperTiles.png", imageManager);

    // initializing the player
    Player player(levels[levelCount].getPlayerSpawn().x,levels[levelCount].getPlayerSpawn().y,levels[levelCount].getTileSize(), imageManager.getTexture("playerSprite"));
    player.initAnimations(5,500);

    // initializing the camera
    Camera2D camera(1280,720,levels[levelCount].getMapSize().x,levels[levelCount].getMapSize().y, levels[levelCount].getTileSize());

    while(window.isOpen())
    {
        // Update
        inputManager.update();
        sf::Event event;

        // Checking if the player has exited the window.
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        switch(ui.getScreenState())
        {
        case UserInterface::TITLE:
        {
            int val = ui.updateTitle(window);

            if(val == 1)
                ui.initInterface(UserInterface::PLAY,imageManager);
            else if (val == 2)
                window.close();
            break;
        }

        case UserInterface::GAMEOVER://, UserInterface::WIN:
            if(inputManager.pressedOnce("confirm"))
                window.close();
            break;

        case UserInterface::WIN:
            if(inputManager.pressedOnce("confirm"))
                window.close();
            break;

        case UserInterface::PLAY:
            if(inputManager.validKeyDown())
            {
                player.update(levels[levelCount], inputManager);
                levels[levelCount].update(player.getGridLocation());
                if(levels[levelCount].isPlayerCrushed())
                {
                    levels[levelCount].loadMap(imageManager);
                    player.decrementLives();
                    player.setGridLocation(levels[levelCount].getPlayerSpawn());
                    player.updateSprite(levels[levelCount].getTileSize());
                    ui.updateLives(levels[levelCount].getPlayerSpawn(), levels[levelCount].getTileSize());
                }

                if(levels[levelCount].getDiamondCollected())
                    ui.updateDiamonds(player.getGridLocation(), levels[levelCount].getTileSize());
            }
            camera.update(player.getGridLocation(), levels[levelCount].getTileSize());
            player.updateAnimations();
            window.setView(camera.getView());
            ui.updatePlay(player.getGridLocation(), levels[levelCount].getTileSize(), player.getRemainingLives(), levels[levelCount].getRemainingDiamonds());

            // Checking if the level has opened
            levels[levelCount].checkExit(player.getGridLocation());

            // Checking if the level has been cleared
            if(levels[levelCount].isCleared() && levelCount < 4)
            {
                levelCount++;
                //level = Level(levelCount, "assets/tilesheets/upperTiles.png", imageManager);
                camera = Camera2D(1280,720,levels[levelCount].getMapSize().x,levels[levelCount].getMapSize().y, levels[levelCount].getTileSize());
                player.setGridLocation(levels[levelCount].getPlayerSpawn());
            }

            // Checking if the game has ended
            if(levels[levelCount].isCleared() && levelCount == 4)
                ui.initInterface(UserInterface::WIN, imageManager);
            if (player.getRemainingLives() == 0)
                ui.initInterface(UserInterface::GAMEOVER, imageManager);
            break;
        }

        // Render
        window.clear();
        // Drawing things relative to the camera
        if(ui.getScreenState() == UserInterface::PLAY)
        {
            levels[levelCount].draw(window);
            player.draw(window);
        }
        ui.drawRelative(window);

        // Drawing things relative to the screen
        window.setView(window.getDefaultView());
        ui.drawAbsolute(window);
        window.display();
    }
    return 0;
}
