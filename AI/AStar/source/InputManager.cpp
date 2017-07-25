#include "InputManager.h"
#include "Renderer.h"

InputManager* InputManager::getInstance()
{
    static InputManager instance;
    return &instance;
}

void InputManager::update(sf::Event & currentEvent)
{
    leftclicking = false;
    rightclicking = false;

    if (currentEvent.type == sf::Event::EventType::MouseButtonPressed)
    {
        if (currentEvent.mouseButton.button == sf::Mouse::Button::Left)
        {
            leftclicking = true;
            leftholding = true;
        }
        if (currentEvent.mouseButton.button == sf::Mouse::Button::Right)
        {
            rightclicking = true;
            rightholding = true;
        }
    }
    if (currentEvent.type == sf::Event::EventType::MouseButtonReleased)
    {
        if (currentEvent.mouseButton.button == sf::Mouse::Button::Left)
        {
            leftholding = false;
        }
        if (currentEvent.mouseButton.button == sf::Mouse::Button::Right)
        {
            rightholding = false;
        }
    }
}

bool InputManager::getLeftClick()
{
    return leftclicking;
}

bool InputManager::getLeftHold()
{
    return leftholding;
}

bool InputManager::getRightClick()
{
    return rightclicking;
}

bool InputManager::getRightHold()
{
    return rightholding;
}

bool InputManager::getHovering(sf::Sprite* graphic)
{
    return graphic->getGlobalBounds().contains(getMousePosf());
}

bool InputManager::getHovering(sf::CircleShape* circleShape)
{
    return circleShape->getGlobalBounds().contains(getMousePosf());
}

bool InputManager::getHovering(sf::RectangleShape* rectangleShape)
{
    return rectangleShape->getGlobalBounds().contains(getMousePosf());
}

sf::Vector2f InputManager::getMousePosf()
{
    return sf::Vector2f(sf::Mouse::getPosition(Renderer::getInstance()->getWindow()));
}

sf::Vector2i InputManager::getMousePosi()
{
    return sf::Mouse::getPosition(Renderer::getInstance()->getWindow());
}
