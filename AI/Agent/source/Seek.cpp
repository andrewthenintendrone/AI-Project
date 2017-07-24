#include "Seek.h"
#include "SFML\Graphics.hpp"
#include "Agent.h"
#include "VectorMaths.h"

// sets target in constructor
Seek::Seek(GameObject* newTarget)
{
    m_target = newTarget;
}

// moves towards target
void Seek::Update(Agent *pAgent)
{
    // Calculate the desired velocity
    sf::Vector2f desiredVelocity = (m_target->getAgent()->getPosition() - pAgent->getPosition());
    float distance = magnitude(desiredVelocity);

    // Check the distance to detect whether the character
    // is inside the slowing area
    if (distance < m_slowingRange)
    {
        // Inside the slowing area
        desiredVelocity = normalize(desiredVelocity, m_maxVelocity * (distance / m_slowingRange));
    }
    else
    {
        // Outside the slowing area.
        desiredVelocity = normalize(desiredVelocity, m_maxVelocity);
    }

    sf::Vector2f steering = (desiredVelocity - pAgent->getVelocity());

    desiredVelocity = truncate(pAgent->getVelocity() + steering, m_maxSpeed);

    pAgent->setVelocity(desiredVelocity);

    // flip sprite to match velocity
    if (pAgent->getParentPointer()->getSprite())
    {
        if (pAgent->getVelocity().x < 0)
        {
            pAgent->getParentPointer()->getSprite()->setScale(-1, 1);
        }
        else if (pAgent->getVelocity().x > 0)
        {
            pAgent->getParentPointer()->getSprite()->setScale(1, 1);
        }
    }
}