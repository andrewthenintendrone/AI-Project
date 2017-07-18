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
    sf::Vector2f desiredVelocity = m_target->getAgent()->getPosition() - pAgent->getPosition();
    normalize(desiredVelocity);
    desiredVelocity *= seekSpeed;

    sf::Vector2f steering = desiredVelocity - pAgent->getVelocity();
    

    //if (pAgent->getParentPointer()->getSprite())
    //{
    //    // flip sprite to direction
    //    if (pAgent->getForce().x < 0)
    //    {
    //        pAgent->getParentPointer()->getSprite()->setScale(-1, 1);
    //    }
    //    else if (pAgent->getForce().x > 0)
    //    {
    //        pAgent->getParentPointer()->getSprite()->setScale(1, 1);
    //    }
    //}
}