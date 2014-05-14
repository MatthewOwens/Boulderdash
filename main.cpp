#include <iostream>
#include <SFML/Graphics.hpp>
#include "ImageManager.h"
#include "Level.h"

int main()
{
    // Initilizing the SFML Window
    sf::RenderWindow window(sf::VideoMode(1280,720), "IT LIVES");
    window.setFramerateLimit(60);
    ImageManager imageManager;
    Level testLevel("levels/testLevel/", "woopwoop", imageManager);

    while(window.isOpen())
    {
        // Update
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Render
        window.clear();
        window.display();
    }
}
