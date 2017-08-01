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
    sf::Vector2f target = getTarget();

    sf::Vector2f velocity = normalize(target, m_maxVelocity);
    sf::Vector2f force = velocity - m_myAgent->getVelocity();

    return force;
}

// returns a target position based on the pressed keys
sf::Vector2f KeyboardControl::getTarget()
{
    // create target with default value of (0, 0)
    sf::Vector2f target;

    // add to the target based on the pressed keys
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        target += (sf::Vector2f(-1, 0));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        target += (sf::Vector2f(1, 0));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        target += (sf::Vector2f(0, -1));
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        target += (sf::Vector2f(0, 1));
    }

    // return the target
    return target;
}
