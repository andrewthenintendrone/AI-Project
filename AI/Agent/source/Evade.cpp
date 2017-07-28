#include "Evade.h"
#include "SFML\Graphics.hpp"
#include "GameObject.h"
#include "Agent.h"
#include "VectorMaths.h"

// set the target and optionally the maximum velocity in the constructor
Evade::Evade(GameObject* newTarget, float maxVelocity, float arriveRange, float mass)
{
    m_target = newTarget;
    m_maxVelocity = maxVelocity;
    m_slowingRange = arriveRange;
    m_mass = mass;
}

// moves towards target
sf::Vector2f Evade::update()
{
    sf::Vector2f velocity = (m_myAgent->getPosition() - m_target->getAgent()->getPosition() + m_target->getAgent()->getVelocity());
    sf::Vector2f force = normalize(velocity, m_maxVelocity) - m_myAgent->getVelocity();

    return force;
}