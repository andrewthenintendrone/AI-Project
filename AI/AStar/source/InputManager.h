#pragma once
#include "SFML\Graphics.hpp"

class InputManager
{
public:
    static InputManager* getInstance();

    void update();

    bool getLeftClick();
    bool getLeftHold();

    bool getLeftRelease();
    bool getRightRelease();

    bool getRightClick();
    bool getRightHold();

    bool getHovering(sf::Sprite* sprite);
    bool getHovering(sf::CircleShape* circleShape);
    bool getHovering(sf::RectangleShape* circleShape);

    sf::Vector2f getMousePosf();
    sf::Vector2i getMousePosi();

private:
    bool leftclicking = false;
    bool rightclicking = false;

    bool leftholding = false;
    bool rightholding = false;

    bool leftreleasing = false;
    bool rightreleasing = false;
};