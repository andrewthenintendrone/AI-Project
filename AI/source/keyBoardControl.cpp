#include "keyBoardControl.h"
#include "SFML\Graphics.hpp"
#include "Agent.h"

void keyBoardControl::Update(Agent* pAgent)
{
    // reset force
    pAgent->setVelocity(sf::Vector2f(0, 0));

    // check keys
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        pAgent->addVelocity(sf::Vector2f(-moveSpeed, 0));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        pAgent->addVelocity(sf::Vector2f(moveSpeed, 0));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        pAgent->addVelocity(sf::Vector2f(0, -moveSpeed));
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        pAgent->addVelocity(sf::Vector2f(0, moveSpeed));
    }

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