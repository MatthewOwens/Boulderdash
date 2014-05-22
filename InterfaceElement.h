#ifndef INTERFACEELEMENT_H
#define INTERFACEELEMENT_H
#include <SFML/Graphics.hpp>

class InterfaceElement
{
    friend class UserInterface;

    public:
        InterfaceElement(int x, int y, bool camRelative = false);
        InterfaceElement(int x, int y, std::string text, sf::Font& font, int textX = 0, int textY = 0, bool camRelative = false);
        InterfaceElement();
        void draw(sf::RenderWindow& window);
        virtual ~InterfaceElement();
    private:
        sf::Vector2i location;
        bool cameraRelative;
        sf::Sprite sprite;
        bool clicked;
        sf::Text headerText;
};

#endif // INTERFACEELEMENT_H
