#include "Wander.h"
#include "SFML\Graphics.hpp"
#include "GameObject.h"
#include "Agent.h"
#include "VectorMaths.h"
#include "Renderer.h"

Wander::Wander(float maxVelocity, float wanderRadius, float wanderDistance, float wanderJitterAmount)
{
    m_maxVelocity = maxVelocity;
    m_wanderRadius = wanderRadius;
    m_wanderDistance = wanderDistance;
    m_wanderJitterAmount = wanderJitterAmount;
}

// wanders aimlessly
sf::Vector2f Wander::update()
{
    sf::Vector2f target = getRandomVector(m_wanderRadius);

    sf::Vector2f jitter = getRandomVector(m_wanderJitterAmount);

    target = (m_myAgent->getPosition() + normalize(target + jitter, m_wanderRadius));

    target += normalize(m_myAgent->getVelocity(), m_wanderDistance);

    sf::Vector2f velocity = target - m_myAgent->getPosition();
    sf::Vector2f force = velocity - m_myAgent->getVelocity();

    // keep within the window
    sf::Vector2f windowSize = Renderer::getInstance()->getWindowSizef();
    if (m_myAgent->getPosition().x <= 0)
    {
        force.x = fabsf(force.x);
    }
    else if (m_myAgent->getPosition().x >= windowSize.x)
    {
        force.x = -fabsf(force.x);
    }
    if (m_myAgent->getPosition().y <= 0)
    {
        force.y = fabsf(force.y);
    }
    else if(m_myAgent->getPosition().y >= windowSize.y)
    {
        force.y = -fabsf(force.y);
    }

    return force;
}