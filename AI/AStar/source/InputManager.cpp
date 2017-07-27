#include "InputManager.h"
#include "Renderer.h"

InputManager* InputManager::getInstance()
{
    static InputManager instance;
    return &instance;
}

void InputManager::update()
{
    sf::Event event;
    event.type = sf::Event::EventType::GainedFocus;
    Renderer::getInstance()->getWindow()->pollEvent(event);

    // deal with closing
    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
    {
        Renderer::getInstance()->closeWindow();
    }
    if (event.type == sf::Event::Closed)
    {
        Renderer::getInstance()->closeWindow();
    }

    leftclicking = false;
    rightclicking = false;
    leftreleasing = false;
    rightreleasing = false;

    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Button::Left)
        {
            leftclicking = true;
            leftholding = true;
        }
        if (event.mouseButton.button == sf::Mouse::Button::Right)
        {
            rightclicking = true;
            rightholding = true;
        }
    }
    if (event.type == sf::Event::MouseButtonReleased)
    {
        if (event.mouseButton.button == sf::Mouse::Button::Left)
        {
            leftreleasing = true;
            leftholding = false;
        }
        if (event.mouseButton.button == sf::Mouse::Button::Right)
        {
            rightreleasing = true;
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

bool InputManager::getLeftRelease()
{
    return leftreleasing;
}

bool InputManager::getRightRelease()
{
    return rightreleasing;
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
    return sf::Vector2f(sf::Mouse::getPosition(*Renderer::getInstance()->getWindow()));
}

sf::Vector2i InputManager::getMousePosi()
{
    return sf::Mouse::getPosition(*Renderer::getInstance()->getWindow());
}
