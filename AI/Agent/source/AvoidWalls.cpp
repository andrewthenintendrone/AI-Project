#include "AvoidWalls.h"
#include "VectorMaths.h"
#include "Agent.h"
#include "Wall.h"
#include "Renderer.h"

AvoidWalls::AvoidWalls(std::list<Wall*>& walls, float maximumVelocity, float feelerDistance)
{
    m_walls = walls;
    m_maximumVelocity = maximumVelocity;
    m_feelerDistance = feelerDistance;
}

AvoidWalls::~AvoidWalls()
{

}

sf::Vector2f AvoidWalls::update()
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

    // keep within the window
    sf::Vector2f windowSize = Renderer::getInstance()->getWindowSizef();
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
    }

    return force;
}
