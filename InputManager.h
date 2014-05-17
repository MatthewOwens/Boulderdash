#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H
#include <SFML/Window.hpp>

class InputManager
{
    public:
        InputManager();
        virtual ~InputManager();
        void update();
        bool pressedOnce(sf::Keyboard::Key keycheck);
    private:
        bool pressedKeys[sf::Keyboard::KeyCount];
        bool previousPressedKeys[sf::Keyboard::KeyCount];
};

#endif // INPUTMANAGER_H
