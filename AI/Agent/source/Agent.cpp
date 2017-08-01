#include "Agent.h"
#include "GameObject.h"
#include "IBehavior.h"
#include "TimeManager.h"
#include "VectorMaths.h"
#include <algorithm>

#pragma region constructor / destructor

// constructor
Agent::Agent(GameObject* parent)
{
    m_parentPointer = parent;
}

// destructor
Agent::~Agent()
{
    for (auto iter = m_behaviours.begin(); iter != m_behaviours.end(); iter++)
    {
        delete (*iter);
    }
}

#pragma endregion


#pragma region access behaviors

void Agent::addBehaviour(IBehavior* newBehaviour, float newWeight)
{
    newBehaviour->m_myAgent = this;
    newBehaviour->m_weight = newWeight;
    m_behaviours.push_back(newBehaviour);
}

void Agent::removeBehavior()
{
    m_behaviours.pop_back();
}

#pragma endregion

#pragma region access velocity

// get velocity
sf::Vector2f Agent::getVelocity()
{
    return m_velocity;
}

// set velocity
void Agent::setVelocity(sf::Vector2f newVelocity)
{
    m_velocity = newVelocity;
}

// add to velocity
void Agent::addVelocity(sf::Vector2f velocityToAdd)
{
    m_velocity += velocityToAdd;
}

#pragma endregion

#pragma region access position

// get position
sf::Vector2f Agent::getPosition()
{
    return m_position;
}

// set position
void Agent::setPosition(sf::Vector2f newPosition)
{
    m_position = newPosition;
}

#pragma endregion

#pragma region access rotation

// get rotation
float Agent::getRotation()
{
    return m_rotation;
}

// set rotation
void Agent::setRotation(float newRotation)
{
    m_rotation = newRotation;
}

#pragma endregion

// get parent pointer
GameObject* Agent::getParentPointer()
{
    return m_parentPointer;
}

// update
void Agent::update()
{
    // TODO: Sensing Calculations
    // TODO: Thinking Calculations
    // Add or remove behaviours from the m_behaviours list
    // Acting:
    for (std::list<IBehavior*>::iterator iter = m_behaviours.begin(); iter != m_behaviours.end(); iter++)
    {
        m_velocity += (*iter)->update();
    }

    //TODO: Physics stuff with force, acceleration, velocity etc...
    m_velocity = truncate(m_velocity, m_maxSpeed);
    m_position += m_velocity * TIMEMANAGER->deltaTime();
}

void Agent::sense()
{

}

void Agent::think()
{

}

void Agent::act()
{

}