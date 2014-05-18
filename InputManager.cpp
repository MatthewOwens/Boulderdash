#include "InputManager.h"
#include <iostream>

InputManager::InputManager()
{
    //ctor
}

InputManager::~InputManager()
{
    //dtor
}

void InputManager::update()
{
    for(int i = 0; i < sf::Keyboard::KeyCount; i++)
    {
        previousPressedKeys[i] = pressedKeys[i];
        pressedKeys[i] = sf::Keyboard::isKeyPressed( (sf::Keyboard::Key)i );
    }
}

bool InputManager::pressedOnce(sf::Keyboard::Key keycheck)
{
    if(pressedKeys[keycheck] && !previousPressedKeys[keycheck])
        return true;
    else return false;
}
