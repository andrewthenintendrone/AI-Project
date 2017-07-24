#include "Flock.h"
#include "Agent.h"
#include "ObjectPool.h"
#include "GameObject.h"
#include "VectorMaths.h"
#include "Renderer.h"

Flock::Flock(GameObject* newTarget)
{
    m_target = newTarget;
}

void Flock::Update(Agent* pAgent)
{
    pAgent->setVelocity(sf::Vector2f(0, 0));
    sf::Vector2f toPlayer = (m_target->getAgent()->getPosition() - pAgent->getPosition());
    float speedFactor = powf(magnitude(toPlayer), 0.3f);

    if (magnitude(m_target->getAgent()->getPosition() - pAgent->getPosition()) > 32)
    {
        std::vector<GameObject*>objects = ObjectPool::getInstance()->getPool();

        sf::Vector2f movement = (computeMovement(pAgent) * m_movementWeight);
        sf::Vector2f alignment = computeAlignment(pAgent, objects) * m_alignmentWeight;
        sf::Vector2f cohesion = computeCohesion(pAgent, objects) * m_cohesionWeight;
        sf::Vector2f seperation = computeSeperation(pAgent, objects) * m_seperationWeight;

        sf::Vector2f finalForce = (movement + alignment + cohesion + seperation);
        normalize(finalForce);
        finalForce *= m_flockSpeed * speedFactor;

        pAgent->setVelocity(finalForce);
    }

    // loop screen
    /*if (pAgent->getPosition().x > Renderer::getInstance()->getWindow().getSize().x)
    {
    pAgent->setPosition(sf::Vector2f(0, pAgent->getPosition().y));
    }
    else if (pAgent->getPosition().x < -32)
    {
    pAgent->setPosition(sf::Vector2f(Renderer::getInstance()->getWindow().getSize().x, pAgent->getPosition().y));
    }
    if (pAgent->getPosition().y > Renderer::getInstance()->getWindow().getSize().y)
    {
    pAgent->setPosition(sf::Vector2f(pAgent->getPosition().x, 0));
    }
    else if (pAgent->getPosition().y < -32)
    {
    pAgent->setPosition(sf::Vector2f(pAgent->getPosition().x, Renderer::getInstance()->getWindow().getSize().y));
    }*/
}

sf::Vector2f Flock::computeMovement(Agent* pAgent)
{
    sf::Vector2f forceVector = (m_target->getAgent()->getPosition() - pAgent->getPosition());
    normalize(forceVector);
    return forceVector;
}

sf::Vector2f Flock::computeAlignment(Agent* pAgent, std::vector<GameObject*> objects)
{
    sf::Vector2f forceVector = sf::Vector2f(0, 0);
    float numNeighbors = 0;

    for each(GameObject* gameobject in objects)
    {
        if (gameobject->getAgent() != pAgent && gameobject != m_target)
        {
            if (magnitude(pAgent->getPosition() - gameobject->getAgent()->getPosition()) < 1000)
            {
                forceVector += gameobject->getAgent()->getVelocity();
                numNeighbors++;
            }
        }
    }

    if (numNeighbors > 0)
    {
        forceVector /= numNeighbors;
        normalize(forceVector);
    }

    return forceVector;
}

sf::Vector2f Flock::computeCohesion(Agent* pAgent, std::vector<GameObject*> objects)
{
    sf::Vector2f forceVector = sf::Vector2f(0, 0);
    float numNeighbors = 0;

    for each(GameObject* gameobject in objects)
    {
        if (gameobject->getAgent() != pAgent && gameobject != m_target)
        {
            if (magnitude(gameobject->getAgent()->getPosition() - pAgent->getPosition()) < 200)
            {
                forceVector += gameobject->getAgent()->getPosition();
                numNeighbors++;
            }
        }
    }

    if (numNeighbors > 0)
    {
        forceVector /= numNeighbors;

        forceVector = forceVector - pAgent->getPosition();

        normalize(forceVector);
    }

    return forceVector;
}

sf::Vector2f Flock::computeSeperation(Agent* pAgent, std::vector<GameObject*> objects)
{
    sf::Vector2f forceVector;

    for each(GameObject* gameobject in objects)
    {
        if (gameobject->getAgent() != pAgent && gameobject != m_target)
        {
            if (magnitude(gameobject->getAgent()->getPosition() - pAgent->getPosition()) < 32)
            {
                forceVector += gameobject->getAgent()->getPosition() - pAgent->getPosition();
            }
        }
    }

    forceVector *= -1.0f;
    normalize(forceVector);
    return forceVector;
}
