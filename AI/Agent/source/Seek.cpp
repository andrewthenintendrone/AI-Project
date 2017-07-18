#include "Seek.h"
#include "SFML\Graphics.hpp"
#include "Agent.h"
#include "VectorMaths.h"
#include "TimeManager.h"

// sets target in constructor
Seek::Seek(GameObject* newTarget)
{
    m_target = newTarget;
}

// moves towards target
void Seek::Update(Agent *pAgent)
{
    // reset force
    pAgent->setVelocity(sf::Vector2f(0, 0));

    sf::Vector2f desiredVelocity = m_target->getAgent()->getPosition() - pAgent->getPosition();
    if (magnitude(desiredVelocity) < 32)
    {
        return;
    }
    normalize(desiredVelocity);
    desiredVelocity *= seekSpeed;

    pAgent->addVelocity(desiredVelocity);

    if (pAgent->getParentPointer()->getSprite())
    {
        // flip sprite to direction
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