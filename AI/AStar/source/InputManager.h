#pragma once
#include "SFML\Graphics.hpp"

enum class MOUSEBUTTONSTATE { IDLE, CLICKED, HELD, RELEASED};

class InputManager
{
public:

    static InputManager* getInstance();

    void update();

    // access state of left mouse button
    bool getLeftClick();
    bool getLeftHold();
    bool getLeftRelease();

    // access state of left mouse button
    bool getRightClick();
    bool getRightHold();
    bool getRightRelease();

    // check if the mouse is hovering over a specific graphic
    bool getHovering(sf::Sprite* sprite);
    bool getHovering(sf::CircleShape* circleShape);
    bool getHovering(sf::RectangleShape* circleShape);

    // access the current mouse position
    sf::Vector2f getMousePosf();
    sf::Vector2i getMousePosi();

private:

    // store state of left and right mouse buttons
    MOUSEBUTTONSTATE leftMouseButton = MOUSEBUTTONSTATE::IDLE;
    MOUSEBUTTONSTATE rightMouseButton = MOUSEBUTTONSTATE::IDLE;

    void handleMouseTransitions(MOUSEBUTTONSTATE& currentState);
    void handleMouseDown(MOUSEBUTTONSTATE& currentState);
    void handleMouseUp(MOUSEBUTTONSTATE& currentState);
};