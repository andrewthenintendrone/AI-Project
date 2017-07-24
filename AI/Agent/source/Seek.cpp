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
    sf::Vector2f velocity = normalize(m_target->getAgent()->getPosition() - pAgent->getPosition(), m_maxVelocity);
    sf::Vector2f force = (velocity - pAgent->getVelocity());

    pAgent->addVelocity(force);

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