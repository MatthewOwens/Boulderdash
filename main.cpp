#include <iostream>
#include <SFML/Graphics.hpp>
#include "ImageManager.h"
#include "Level.h"
#include "Camera2D.h"
#include "InputManager.h"

int main()
{
    // Initilizing the SFML Window
    sf::RenderWindow window(sf::VideoMode(1280,720), "Boulderdash");
    window.setFramerateLimit(60);
    ImageManager imageManager;
    InputManager inputManager;
    Level testLevel("levels/testLevel/", "assets/tilesheets/upperTiles.png", imageManager);

    while(window.isOpen())
    {
        // Update
        inputManager.update();
        sf::Event event;
        while(window.pollEvent(event))
        {

        }
        if(inputManager.pressedOnce(sf::Keyboard::B))
            testLevel.update();

        // Render
        window.clear();
        testLevel.draw(window);
        window.display();
    }
}
