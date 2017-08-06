#include "InputManager.h"
#include "Renderer.h"

// there is only ever one InputManager
InputManager* InputManager::getInstance()
{
    static InputManager instance;
    return &instance;
}

// update function
void InputManager::update()
{
    sf::Event event;

    // without this line the window can randomly close
    event.type = static_cast<sf::Event::EventType>(1);

    Renderer::getInstance()->getWindow()->pollEvent(event);

    // window will close if the close button is clicked or the user presses the escape key
    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape)
    {
        Renderer::getInstance()->closeWindow();
    }
    else if(event.type == sf::Event::Closed)
    {
        Renderer::getInstance()->closeWindow();
    }

    // deal with transitions
    handleMouseTransitions(leftMouseButton);
    handleMouseTransitions(rightMouseButton);

    // the current event is a mouse button press
    if (event.type == sf::Event::MouseButtonPressed)
    {
        handleMouseDown(event.mouseButton.button == sf::Mouse::Button::Left ? leftMouseButton : rightMouseButton);
    }

    // the current event is a mouse button release
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        handleMouseUp(event.mouseButton.button == sf::Mouse::Button::Left ? leftMouseButton : rightMouseButton);
    }
}

// returns wheather the left mouse button is being clicked
bool InputManager::getLeftClick()
{
    return leftMouseButton == MOUSEBUTTONSTATE::CLICKED;
}

// returns wheather the left mouse button is being held
bool InputManager::getLeftHold()
{
    return leftMouseButton == MOUSEBUTTONSTATE::HELD;
}

// returns wheather the left mouse button is being released
bool InputManager::getLeftRelease()
{
    return leftMouseButton == MOUSEBUTTONSTATE::RELEASED;
}

// returns wheather the right mouse button is being clicked
bool InputManager::getRightClick()
{
    return rightMouseButton == MOUSEBUTTONSTATE::CLICKED;
}

// returns wheather the right mouse button is being held
bool InputManager::getRightHold()
{
    return leftMouseButton == MOUSEBUTTONSTATE::HELD;
}

// returns wheather the right mouse button is being released
bool InputManager::getRightRelease()
{
    return rightMouseButton == MOUSEBUTTONSTATE::RELEASED;
}

// returns wheather the mouse is hovering over the specified sprite
bool InputManager::getHovering(sf::Sprite* graphic)
{
    return graphic->getGlobalBounds().contains(getMousePosf());
}

// returns wheather the mouse is hovering over the specified circle shape
bool InputManager::getHovering(sf::CircleShape* circleShape)
{
    return circleShape->getGlobalBounds().contains(getMousePosf());
}

// returns wheather the mouse is hovering over the specified rectangle shape
bool InputManager::getHovering(sf::RectangleShape* rectangleShape)
{
    return rectangleShape->getGlobalBounds().contains(getMousePosf());
}

// returns the current mouse position relative to the window as an sf::Vector2f (floats)
sf::Vector2f InputManager::getMousePosf()
{
    return sf::Vector2f(sf::Mouse::getPosition(*Renderer::getInstance()->getWindow()));
}

// returns the current mouse position relative to the window as an sf::Vector2i (ints)
sf::Vector2i InputManager::getMousePosi()
{
    return sf::Mouse::getPosition(*Renderer::getInstance()->getWindow());
}

// handle the one frame transitions from click to hold and from release to idle
void InputManager::handleMouseTransitions(MOUSEBUTTONSTATE& currentPosition)
{
    // after one frame a click becomes a hold
    if (currentPosition == MOUSEBUTTONSTATE::CLICKED)
    {
        currentPosition = MOUSEBUTTONSTATE::HELD;
    }
    // after one frame a release becomes an idle
    else if (currentPosition == MOUSEBUTTONSTATE::RELEASED)
    {
        currentPosition = MOUSEBUTTONSTATE::IDLE;
    }
}

// handle a mouse button being down
void InputManager::handleMouseDown(MOUSEBUTTONSTATE& currentState)
{
    // only transition into a click from idle or release
    if (currentState == MOUSEBUTTONSTATE::IDLE || currentState == MOUSEBUTTONSTATE::RELEASED)
    {
        currentState = MOUSEBUTTONSTATE::CLICKED;
    }
}

// handle a mouse button being up
void InputManager::handleMouseUp(MOUSEBUTTONSTATE& currentState)
{
    // only transition into a realease from click or hold
    if (currentState == MOUSEBUTTONSTATE::CLICKED || currentState == MOUSEBUTTONSTATE::HELD)
    {
        currentState = MOUSEBUTTONSTATE::RELEASED;
    }
}
