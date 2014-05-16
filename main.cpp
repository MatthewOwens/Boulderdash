#include <iostream>
#include <SFML/Graphics.hpp>
#include "ImageManager.h"
#include "Level.h"
#include "Camera2D.h"

int main()
{
    // Initilizing the SFML Window
    sf::RenderWindow window(sf::VideoMode(1280,720), "Boulderdash");
    window.setFramerateLimit(60);
    ImageManager imageManager;
    Level testLevel("levels/testLevel/", "assets/tilesheets/upperTiles.png", imageManager);

    Camera2D camera(1280,720,21,13,64);

    while(window.isOpen())
    {
        // Update
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                camera.move(3,0);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                camera.move(-3,0);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                camera.move(0,-3);
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                camera.move(0,3);

            camera.update(sf::Vector2f());
        }

        // Render
        window.clear();
        window.setView(camera.getView());
        testLevel.draw(window);
        window.display();
    }
}
