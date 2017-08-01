#include "FlipSprite.h"
#include "GameObject.h"

// flips the sprite based on the velocity of the agent
sf::Vector2f FlipSprite::update()
{
    if (m_myAgent->getVelocity().x > 0)
    {
        m_myAgent->getParentPointer()->getSprite()->setScale(sf::Vector2f(1, 1));
    }
    else if(m_myAgent->getVelocity().x < 0)
    {
        m_myAgent->getParentPointer()->getSprite()->setScale(sf::Vector2f(-1, 1));
    }

    return sf::Vector2f(0, 0);
}
