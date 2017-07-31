#include "Flock.h"
#include "Agent.h"
#include "ObjectPool.h"
#include "GameObject.h"
#include "VectorMaths.h"
#include "Renderer.h"

Flock::Flock(std::list<GameObject*>& flock, float maximumVelocity)
{
    m_flock = flock;
    m_maximumVelocity = maximumVelocity;
}

sf::Vector2f Flock::update()
{
    sf::Vector2f windowSize = Renderer::getInstance()->getWindowSizef();
    sf::Vector2f myPos = m_myAgent->getPosition();

    if (myPos.x < 0)
    {
        m_myAgent->setPosition(sf::Vector2f(windowSize.x, myPos.y));
    }
    else if (myPos.x > windowSize.x)
    {
        m_myAgent->setPosition(sf::Vector2f(0, myPos.y));
    }

    if (myPos.y < 0)
    {
        m_myAgent->setPosition(sf::Vector2f(myPos.x, windowSize.y));
    }
    else if (myPos.y > windowSize.y)
    {
        m_myAgent->setPosition(sf::Vector2f(myPos.x, 0));
    }


    sf::Vector2f alignment = computeAlignment() * m_alignmentWeight;
    sf::Vector2f cohesion = computeCohesion(m_cohesionRadius) * m_cohesionWeight;
    sf::Vector2f seperation = -computeCohesion(m_seperationRadius) * m_seperationWeight;

    sf::Vector2f velocity = alignment + cohesion + seperation;
    velocity = normalize(velocity, m_maximumVelocity);

    sf::Vector2f force = velocity - m_myAgent->getVelocity();

    return force;
}

sf::Vector2f Flock::computeAlignment()
{
    sf::Vector2f target;
    int numNeighbors = 0;

    for each(GameObject* gameobject in m_flock)
    {
        if (gameobject->getAgent() != m_myAgent)
        {
            if (magnitude(gameobject->getAgent()->getPosition()) < m_alignmentRadius)
            {
                target += gameobject->getAgent()->getVelocity();
                numNeighbors++;
            }
        }
    }

    if (numNeighbors > 0)
    {
        target /= (float)numNeighbors;
    }

    target = normalize(target, m_maximumVelocity);

    return target;
}

sf::Vector2f Flock::computeCohesion(float radius)
{
    sf::Vector2f target;
    int numNeighbors = 0;

    for each(GameObject* gameobject in m_flock)
    {
        if (gameobject->getAgent() != m_myAgent)
        {
            if (magnitude(gameobject->getAgent()->getPosition() - m_myAgent->getPosition()) < radius)
            {
                target += gameobject->getAgent()->getPosition();
                numNeighbors++;
            }
        }
    }

    if (numNeighbors > 0)
    {
        target /= (float)numNeighbors;
    }

    target = normalize(target, m_maximumVelocity);

    return target;
}
