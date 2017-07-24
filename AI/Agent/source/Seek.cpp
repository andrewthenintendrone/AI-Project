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
    sf::Vector2f desiredVelocity = normalize(m_target->getAgent()->getPosition() - pAgent->getPosition(), m_maxVelocity);
    sf::Vector2f steering = normalize(desiredVelocity - pAgent->getVelocity(), m_maxForce / m_mass);

    pAgent->setVelocity(normalize(pAgent->getVelocity() + steering, m_maxSpeed));

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