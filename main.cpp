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
    Level level("levels/", "assets/tilesheets/upperTiles.png", imageManager);
    Player player(level.getPlayerSpawn().x,level.getPlayerSpawn().y,level.getTileSize(), imageManager.getTexture("playerSprite"));
    player.initAnimations(5,500);
    Camera2D camera(1280,720,level.getMapSize().x,level.getMapSize().y, level.getTileSize());

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
                player.update(level, inputManager);
                level.update(player.getGridLocation());
                if(level.isPlayerCrushed())
                {
                    level.loadMap(imageManager);
                    player.decrementLives();
                    player.setGridLocation(level.getPlayerSpawn());
                    player.updateSprite(level.getTileSize());
                    ui.updateLives(level.getPlayerSpawn(), level.getTileSize());
                }

                if(level.getDiamondCollected())
                    ui.updateDiamonds(player.getGridLocation(), level.getTileSize());
            }
            camera.update(player.getGridLocation(), level.getTileSize());
            player.updateAnimations();
            window.setView(camera.getView());
            ui.updatePlay(player.getGridLocation(), level.getTileSize(), player.getRemainingLives(), level.getRemainingDiamonds());

            // Checking if the game has ended
            if(level.getRemainingDiamonds() == 0)
                ui.initInterface(UserInterface::WIN, imageManager);
            else if (player.getRemainingLives() == 0)
                ui.initInterface(UserInterface::GAMEOVER, imageManager);
            break;
        }

        // Render
        window.clear();
        // Drawing things relative to the camera
        level.draw(window);
        player.draw(window);
        ui.drawRelative(window);

        // Drawing things relative to the screen
        window.setView(window.getDefaultView());
        ui.drawAbsolute(window);
        window.display();
    }
}
