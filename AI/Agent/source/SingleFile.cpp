#include "SingleFile.h"
#include "SFML\Graphics.hpp"
#include "GameObject.h"
#include "VectorMaths.h"
#include <algorithm>



SingleFile::SingleFile(std::list<GameObject*>* flock, float maxVelocity, float slowRadius, float stopRadius)
{
    m_flock = flock;
    m_maxVelocity = maxVelocity;
    m_slowRadius = slowRadius;
    m_stopRadius = stopRadius;
}

// moves towards target
sf::Vector2f SingleFile::update()
{
    if (m_target == nullptr)
    {
        m_target = *std::prev(std::find(m_flock->begin(), m_flock->end(), m_myAgent->getParentPointer()));
    }
    sf::Vector2f velocity = (m_target->getAgent()->getPosition() - m_myAgent->getPosition());

    if (magnitude(velocity) < m_stopRadius)
    {
        velocity = normalize(velocity, 0.0f);
    }
    else if (magnitude(velocity) < m_slowRadius)
    {
        velocity = normalize(velocity, magnitude(velocity) / m_slowRadius) * m_maxVelocity;
    }
    else
    {
        velocity = normalize(velocity, m_maxVelocity);
    }

    sf::Vector2f force = velocity - m_myAgent->getVelocity();

    return force;
}