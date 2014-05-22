#include "InterfaceElement.h"

InterfaceElement::InterfaceElement(int x, int y, bool camRelative)
{
    location = sf::Vector2i(x,y);
    cameraRelative = camRelative;
    headerText.setString("");
}

// Default constructor
InterfaceElement::InterfaceElement()
{

}

InterfaceElement::InterfaceElement(int x, int y, std::string text, sf::Font& font, int textX, int textY, bool camRelative)
{
    location = sf::Vector2i(x,y);
    sprite.setPosition(x,y);
    headerText.setString(text);
    headerText.setPosition(x + textX, y + textY);
    headerText.setFont(font);
    cameraRelative = camRelative;
}

InterfaceElement::~InterfaceElement()
{
    //dtor
}

void InterfaceElement::draw(sf::RenderWindow& window)
{
    window.draw(sprite);

    if(headerText.getString() != "")
        window.draw(headerText);
}
