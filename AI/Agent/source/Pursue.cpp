#include "Pursue.h"
#include "SFML\Graphics.hpp"
#include "GameObject.h"
#include "VectorMaths.h"
#include "Renderer.h"

// set the target and optionally the maximum velocity in the constructor
Pursue::Pursue(GameObject* newTarget, float maxVelocity)
{
    m_target = newTarget;
    m_maxVelocity = maxVelocity;
}

// moves towards target
sf::Vector2f Pursue::update()
{
    sf::Vector2f velocity = (m_target->getAgent()->getPosition() + m_target->getAgent()->getVelocity() - m_myAgent->getPosition());
    sf::Vector2f force = normalize(velocity, m_maxVelocity) - m_myAgent->getVelocity();

    // keep within the window
    sf::Vector2f windowSize = Renderer::getInstance()->getWindowSizef();
    if (m_myAgent->getPosition().x + force.x < 0 || m_myAgent->getPosition().x + force.x > windowSize.x)
    {
        force.x = -force.x;
    }
    if (m_myAgent->getPosition().y + force.y < 0 || m_myAgent->getPosition().y + force.y > windowSize.y)
    {
        force.y = -force.y;
    }

    return force;
}