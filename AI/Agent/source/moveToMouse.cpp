#include "moveToMouse.h"
#include "Renderer.h"
#include "InputManager.h"
#include "VectorMaths.h"
#include "Agent.h"

moveToMouse::moveToMouse()
{

}

moveToMouse::moveToMouse(float maxVelocity)
{
    m_maxVelocity = maxVelocity;
}

sf::Vector2f moveToMouse::update()
{
    sf::Vector2f force = normalize(InputManager::getInstance()->getMousePosf() - m_myAgent->getPosition(), m_maxVelocity);
    force -= m_myAgent->getVelocity();

    return force;
}