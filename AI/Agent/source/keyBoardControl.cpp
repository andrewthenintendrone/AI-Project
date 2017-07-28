#include "KeyboardControl.h"
#include "SFML\Graphics.hpp"
#include "Agent.h"
#include "VectorMaths.h"

KeyboardControl::KeyboardControl(float maxVelocity)
{
    m_maxVelocity = maxVelocity;
}

sf::Vector2f KeyboardControl::update()
{
    sf::Vector2f desiredVelocity = sf::Vector2f(0, 0);

    bool directionPressed = false;

    // check keys
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        directionPressed = true;
        desiredVelocity += (sf::Vector2f(-1, 0));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        directionPressed = true;
        desiredVelocity += (sf::Vector2f(1, 0));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        directionPressed = true;
        desiredVelocity += (sf::Vector2f(0, -1));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        directionPressed = true;
        desiredVelocity += (sf::Vector2f(0, 1));
    }

    if (directionPressed)
    {
        normalize(desiredVelocity);
        desiredVelocity *= m_maxVelocity;
        return desiredVelocity;
    }
    else
    {
        m_myAgent->setVelocity(desiredVelocity);
        return (desiredVelocity);
    }
}