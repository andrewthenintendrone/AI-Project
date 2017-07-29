#include "SeekMouse.h"
#include "Renderer.h"
#include "InputManager.h"
#include "VectorMaths.h"
#include "Agent.h"

SeekMouse::SeekMouse(float maxVelocity, float approachRadius, float stopRadius)
{
    m_maxVelocity = maxVelocity;
    m_slowRadius = approachRadius;
    m_stopRadius = stopRadius;
}

sf::Vector2f SeekMouse::update()
{
    sf::Vector2f windowSize = Renderer::getInstance()->getWindowSizef();
    sf::Vector2f mousePos = InputManager::getInstance()->getMousePosf();

    if (mousePos.x < 0)
    {
        mousePos.x = 0;
    }
    else if(mousePos.x > windowSize.x)
    {
        mousePos.x = windowSize.x;
    }
    if (mousePos.y < 0)
    {
        mousePos.y = 0;
    }
    else if (mousePos.y > windowSize.y)
    {
        mousePos.y = windowSize.y;
    }

    sf::Vector2f velocity = mousePos - m_myAgent->getPosition();

    if (magnitude(velocity) < m_stopRadius)
    {
        velocity = sf::Vector2f(0, 0);
    }
    else if (magnitude(velocity) < m_slowRadius)
    {
        velocity = normalize(velocity, magnitude(velocity) / m_slowRadius) * m_maxVelocity;
    }
    else
    {
        velocity = normalize(velocity, m_maxVelocity);
    }

    sf::Vector2f force = velocity - m_myAgent->getVelocity();

    return force;
}