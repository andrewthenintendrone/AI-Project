#include "SeekMouse.h"
#include "Renderer.h"
#include "InputManager.h"
#include "VectorMaths.h"
#include "Agent.h"

SeekMouse::SeekMouse(float maxVelocity)
{
    m_maxVelocity = maxVelocity;
}

sf::Vector2f SeekMouse::update()
{
    sf::Vector2f force = normalize(InputManager::getInstance()->getMousePosf() - m_myAgent->getPosition(), m_maxVelocity);
    force -= m_myAgent->getVelocity();

    return force;
}