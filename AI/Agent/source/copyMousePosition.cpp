#include "CopyMousePosition.h"
#include "Agent.h"
#include "InputManager.h"
#include "Renderer.h"

sf::Vector2f CopyMousePosition::update()
{
    m_myAgent->setPosition(sf::Vector2f(InputManager::getInstance()->getMousePosf()));
    return sf::Vector2f(0.0f, 0.0f);
}