#include "Flock.h"
#include "Agent.h"
#include "ObjectPool.h"
#include "GameObject.h"
#include "VectorMaths.h"
#include "Renderer.h"
#include "TimeManager.h"

Flock::Flock(std::list<GameObject*>* flock, float maximumVelocity)
{
    m_flock = *flock;
    m_maximumVelocity = maximumVelocity;
}

sf::Vector2f Flock::update()
{
    /*if (m_myAgent->getPosition().x > windowSize.x || m_myAgent->getPosition().x < 0 || m_myAgent->getPosition().y > windowSize.y || m_myAgent->getPosition().y < 0)
    {
        m_myAgent->setPosition(sf::Vector2f((float)(rand() % windowSize.x), (float)(rand() % windowSize.y)));
        m_myAgent->setVelocity(getRandomVector(1.0f));
    }*/

    sf::Vector2f alignment = computeAlignment();
    alignment = normalize(alignment, m_alignmentWeight * m_maximumVelocity);
    sf::Vector2f cohesion = computeCohesion(m_cohesionRadius);
    cohesion = normalize(cohesion, m_cohesionWeight * m_maximumVelocity);
    sf::Vector2f seperation = -computeCohesion(m_seperationRadius);
    seperation = normalize(seperation, m_seperationWeight * m_maximumVelocity);

    sf::Vector2f velocity = alignment + cohesion + seperation;
    velocity = normalize(velocity, m_maximumVelocity);

    return velocity;
}

sf::Vector2f Flock::computeAlignment()
{
    sf::Vector2f velocity;
    int numNeighbors = 0;

    for each(GameObject* gameobject in m_flock)
    {
        if (gameobject->getAgent() != m_myAgent)
        {
            if (distanceCheck(gameobject->getAgent()->getPosition(), m_myAgent->getPosition(), m_alignmentRadius))
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

    return velocity;
}

sf::Vector2f Flock::computeCohesion(float radius)
{
    sf::Vector2f velocity;
    int numNeighbors = 0;

    for each(GameObject* gameobject in m_flock)
    {
        if (gameobject->getAgent() != m_myAgent)
        {
            if (distanceCheck(gameobject->getAgent()->getPosition(), m_myAgent->getPosition(), radius))
            {
                velocity += gameobject->getAgent()->getPosition() - m_myAgent->getPosition();
                numNeighbors++;
            }
        }
    }

    if (numNeighbors > 0)
    {
        velocity /= (float)numNeighbors;
    }

    velocity = velocity - m_myAgent->getVelocity();

    return velocity;
}
