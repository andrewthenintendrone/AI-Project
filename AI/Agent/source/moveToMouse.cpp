#include "moveToMouse.h"
#include "Renderer.h"
#include "InputManager.h"
#include "VectorMaths.h"
#include "Agent.h"

void moveToMouse::Update(Agent* pAgent)
{
    sf::Vector2f force = normalize(InputManager::getInstance()->getMousePosf() - pAgent->getPosition(), m_maxVelocity);
    force -= pAgent->getVelocity();

    pAgent->addVelocity(force);
}