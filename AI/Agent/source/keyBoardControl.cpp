#include "keyBoardControl.h"
#include "IBehavior.h"
#include "GameObject.h"
#include "SFML\Graphics.hpp"
#include "Agent.h"
#include "VectorMaths.h"

void keyBoardControl::update(Agent* pAgent)
{
    // reset force
    pAgent->setVelocity(sf::Vector2f(0, 0));

    sf::Vector2f desiredVelocity = sf::Vector2f(0, 0);

    // check keys
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        desiredVelocity += (sf::Vector2f(-moveSpeed, 0));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        desiredVelocity += (sf::Vector2f(moveSpeed, 0));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        desiredVelocity += (sf::Vector2f(0, -moveSpeed));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        desiredVelocity += (sf::Vector2f(0, moveSpeed));
    }

    normalize(desiredVelocity);
    desiredVelocity *= moveSpeed;

    pAgent->addVelocity(desiredVelocity);

    // flip sprite to direction
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