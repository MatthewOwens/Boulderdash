#include <iostream>
#include <SFML/Graphics.hpp>
#include "ImageManager.h"
#include "Entity.h"

int main()
{
    // Initilizing the SFML Window
    sf::RenderWindow window(sf::VideoMode(1280,720), "IT LIVES");
    window.setFramerateLimit(60);
    sf::View view;
    view.reset(sf::FloatRect(-50,0,1280,720));
    ImageManager imageManager;
    imageManager.loadImage("assets/sprites/raveSprite.png", "raveSprite");
    Entity entity(0,0, imageManager.getTexture("raveSprite"));
    entity.initAnimations(5,100);

    while(window.isOpen())
    {
        // Update
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        entity.update();
        std::cout << "Entity Updated" << std::endl;

        // Render
        window.clear();
        window.setView(view);
        entity.draw(window);
        window.display();
    }
}
