#include "Flee.h"
#include "SFML\Graphics.hpp"
#include "Agent.h"
#include "VectorMaths.h"

// sets target in constructor
Flee::Flee(GameObject* newTarget)
{
    m_target = newTarget;
}

Flee::Flee(GameObject* newTarget, float maxVelocity)
{
    m_target = newTarget;
    m_maxVelocity = maxVelocity;
}

// moves towards target
sf::Vector2f Flee::update()
{
    sf::Vector2f velocity = normalize(m_myAgent->getPosition() - m_target->getAgent()->getPosition(), m_maxVelocity);
    sf::Vector2f force = velocity - m_myAgent->getVelocity();

    return force;
}