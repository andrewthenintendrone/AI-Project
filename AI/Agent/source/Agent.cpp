#include "Agent.h"
#include "GameObject.h"
#include "IBehavior.h"
#include "TimeManager.h"

Agent::Agent(GameObject* parent)
{
    m_parentPointer = parent;
}

Agent::~Agent()
{
    for (auto iter = m_behaviours.begin(); iter != m_behaviours.end(); iter++)
    {
        delete (*iter);
    }
}

void Agent::addBehaviour(IBehavior* newBehaviour)
{
    m_behaviours.push_back(newBehaviour);
}

void Agent::Update()
{
    // TODO: Sensing Calculations
    // TODO: Thinking Calculations
    // Add or remove behaviours from the m_behaviours list
    // Acting:
    for (std::list<IBehavior*>::iterator iter = m_behaviours.begin(); iter != m_behaviours.end(); iter++)
    {
        (*iter)->Update(this);
    }

    //TODO: Physics stuff with force, acceleration, velocity etc...
    m_position += m_velocity * TIMEMANAGER->deltaTime();
}

void Agent::setVelocity(sf::Vector2f newVelocity)
{
    m_velocity = newVelocity;
}

sf::Vector2f Agent::getVelocity()
{
    return m_velocity;
}

// adds force
void Agent::addVelocity(sf::Vector2f velocityToAdd)
{
    m_velocity += velocityToAdd;
}

void Agent::setPosition(sf::Vector2f newPosition)
{
    m_position = newPosition;
}

sf::Vector2f Agent::getPosition()
{
    return m_position;
}

void Agent::setRotation(float newRotation)
{
    m_rotation = newRotation;
}

float Agent::getRotation()
{
    return m_rotation;
}

void Agent::pushBehaviour(IBehavior* newBehavior)
{
    m_behaviours.push_back(newBehavior);
}

GameObject* Agent::getParentPointer()
{
    return m_parentPointer;
}