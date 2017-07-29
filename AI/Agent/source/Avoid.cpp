#include "Avoid.h"
#include "VectorMaths.h"
#include "Agent.h"
#include "Wall.h"

Avoid::Avoid(std::list<Wall*>& walls, float maximumVelocity, float feelerDistance, float feelerRadius)
{
    m_walls = walls;
    m_maximumVelocity = maximumVelocity;
    m_feelerDistance = feelerDistance;
    m_feelerRadius = feelerRadius;
}

Avoid::~Avoid()
{

}

sf::Vector2f Avoid::update()
{
    sf::Vector2f ray = m_myAgent->getPosition() + normalize(m_myAgent->getVelocity(), m_feelerDistance);

    sf::Vector2f force;

    for each(Wall* currentWall in m_walls)
    {
        if (currentWall->getBounds().contains(ray))
        {
            force += normalize(m_myAgent->getPosition() - currentWall->getPosition(), m_maximumVelocity);
        }
    }

    return force;
}
