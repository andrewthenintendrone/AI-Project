#include "CopyMousePosition.h"
#include "InputManager.h"
#include "Renderer.h"
#include "Agent.h"

sf::Vector2f copyMousePosition::update()
{
    m_myAgent->setPosition(sf::Vector2f(InputManager::getInstance()->getMousePosf()));
    return sf::Vector2f(0.0f, 0.0f);
}