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
    sf::Vector2f alignment = computeAlignment() * m_alignmentWeight;
    sf::Vector2f cohesion = computeCohesion(m_cohesionRadius) * m_cohesionWeight;
    sf::Vector2f seperation = -computeCohesion(m_seperationRadius) * m_seperationWeight;

    sf::Vector2f target = seperation;
    sf::Vector2f velocity = target - m_myAgent->getPosition();

    sf::Vector2f force = velocity - m_myAgent->getVelocity();

    // keep within the window
    /*sf::Vector2f windowSize = Renderer::getInstance()->getWindowSizef();
    if (m_myAgent->getPosition().x <= 0)
    {
        force.x = fabsf(force.x);
    }
    else if (m_myAgent->getPosition().x >= windowSize.x)
    {
        force.x = -fabsf(force.x);
    }
    if (m_myAgent->getPosition().y <= 0)
    {
        force.y = fabsf(force.y);
    }
    else if (m_myAgent->getPosition().y >= windowSize.y)
    {
        force.y = -fabsf(force.y);
    }*/

    return force;
}

sf::Vector2f Flock::computeAlignment()
{
    sf::Vector2f velocity;
    int numNeighbors = 0;

    for each(GameObject* gameobject in m_flock)
    {
        if (gameobject->getAgent() != m_myAgent)
        {
            if (magnitude(gameobject->getAgent()->getPosition()) < m_alignmentRadius)
            {
                velocity += gameobject->getAgent()->getVelocity();
                numNeighbors++;
            }
        }
    }

    if (numNeighbors > 0)
    {
        velocity /= (float)numNeighbors;
    }

    sf::Vector2f force = velocity - m_myAgent->getVelocity();

    return force;
}

sf::Vector2f Flock::computeCohesion(float radius)
{
    sf::Vector2f target = m_myAgent->getPosition();
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

    sf::Vector2f velocity = target - m_myAgent->getPosition();

    sf::Vector2f force = velocity - m_myAgent->getVelocity();

    return force;
}