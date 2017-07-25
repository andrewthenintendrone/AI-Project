#pragma once
#include "SFML\Graphics.hpp"

class InputManager
{
public:
    static InputManager* getInstance();

    void update(sf::Event& currentEvent);

    bool getLeftClick();
    bool getLeftHold();

    bool getRightClick();
    bool getRightHold();

private:
    bool leftclicking = false;
    bool leftholding = false;

    bool rightclicking = false;
    bool rightholding = false;
};