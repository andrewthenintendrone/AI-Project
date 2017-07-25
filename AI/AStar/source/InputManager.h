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

    bool getHovering(sf::Sprite* sprite);
    bool getHovering(sf::CircleShape* circleShape);
    bool getHovering(sf::RectangleShape* circleShape);

    sf::Vector2f getMousePosf();
    sf::Vector2i getMousePosi();

private:
    bool leftclicking = false;
    bool leftholding = false;

    bool rightclicking = false;
    bool rightholding = false;
};