#include "Flock.h"
#include "ObjectPool.h"
#include "VectorMaths.h"

Flock::Flock(GameObject* newTarget)
{
    m_target = newTarget;
}

void Flock::Update(Agent* pAgent)
{
    std::vector<GameObject*>objects = ObjectPool::getInstance()->getPool();

    sf::Vector2f movement = computeMovement(pAgent);
    sf::Vector2f alignment = computeAlignment(pAgent, objects);
    sf::Vector2f cohesion = computeCohesion(pAgent, objects);
    sf::Vector2f seperation = computeSeperation(pAgent, objects);

    sf::Vector2f finalForce = (movement + alignment + cohesion + seperation);
    finalForce = (finalForce / magnitude(finalForce));
    finalForce *= m_flockSpeed;

    pAgent->setVelocity((movement + alignment + cohesion + seperation) * m_flockSpeed);
}

sf::Vector2f Flock::computeMovement(Agent* pAgent)
{
    sf::Vector2f forceVector = (m_target->getAgent()->getPosition() - pAgent->getPosition());
    forceVector /= magnitude(forceVector);
    return forceVector;
}

sf::Vector2f Flock::computeAlignment(Agent* pAgent, std::vector<GameObject*> objects)
{
    sf::Vector2f forceVector;
    float numNeighbors = 0;

    for each(GameObject* gameobject in objects)
    {
        if (gameobject->getAgent() != pAgent && gameobject != m_target)
        {
            forceVector += gameobject->getAgent()->getVelocity();
            numNeighbors++;
        }
    }

    if (numNeighbors > 0)
    {
        forceVector /= numNeighbors;
        forceVector /= magnitude(forceVector);
    }

    return forceVector;
}

sf::Vector2f Flock::computeCohesion(Agent* pAgent, std::vector<GameObject*> objects)
{
    sf::Vector2f forceVector;
    sf::Vector2f centerOfMass;
    float numNeighbors = 0;

    for each(GameObject* gameobject in objects)
    {
        if (gameobject->getAgent() != pAgent && gameobject != m_target)
        {
            centerOfMass += gameobject->getAgent()->getPosition();
            numNeighbors++;
        }
    }

    if (numNeighbors > 0)
    {
        centerOfMass /= numNeighbors;

        forceVector = centerOfMass - pAgent->getPosition();

        forceVector /= magnitude(forceVector);
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
            if (magnitude(gameobject->getAgent()->getPosition() - pAgent->getPosition()) < 64)
            {
                sf::Vector2f headingVector = (pAgent->getPosition() - gameobject->getAgent()->getPosition());
            }
        }
    }

    return forceVector;
}
