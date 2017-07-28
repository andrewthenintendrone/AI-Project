#include "Seek.h"
#include "SFML\Graphics.hpp"
#include "GameObject.h"
#include "VectorMaths.h"

// set the target and optionally the maximum velocity in the constructor
Seek::Seek(GameObject* newTarget, float maxVelocity)
{
    m_target = newTarget;
    m_maxVelocity = maxVelocity;
}

// moves towards target
sf::Vector2f Seek::update()
{
    sf::Vector2f velocity = normalize(m_target->getAgent()->getPosition() - m_myAgent->getPosition(), m_maxVelocity);
    sf::Vector2f force = velocity - m_myAgent->getVelocity();

    return force;
}