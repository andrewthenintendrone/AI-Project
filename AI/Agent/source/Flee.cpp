#include "Flee.h"
#include "SFML\Graphics.hpp"
#include "GameObject.h"
#include "VectorMaths.h"

Flee::Flee(GameObject* newTarget, float detectionRadius, float maxVelocity)
{
    m_target = newTarget;
    m_detectionRadius = detectionRadius;
    m_maxVelocity = maxVelocity;
}

// moves towards target
sf::Vector2f Flee::update()
{
    if (distanceCheck(m_target->getAgent()->getPosition(), m_myAgent->getPosition(), m_detectionRadius))
    {
        sf::Vector2f velocity = normalize(m_myAgent->getPosition() - m_target->getAgent()->getPosition(), m_maxVelocity);
        sf::Vector2f force = velocity - m_myAgent->getVelocity();

        return force;
    }
    else
    {
        return sf::Vector2f(0, 0);
    }
}