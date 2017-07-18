#include "Flock.h"
#include "Agent.h"
#include "ObjectPool.h"
#include "GameObject.h"
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

    sf::Vector2f finalForce = (movement * 0.1f + alignment * 0.25f + cohesion * 0.6f + seperation * 0.85f);
    normalize(finalForce);
    finalForce *= m_flockSpeed;

    pAgent->setVelocity(finalForce * powf(magnitude(m_target->getAgent()->getPosition() - pAgent->getPosition()), 0.1f));
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
            if (magnitude(pAgent->getPosition() - gameobject->getAgent()->getPosition()) < 100)
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
