#include "CopyMousePosition.h"
#include "InputManager.h"
#include "Renderer.h"
#include "Agent.h"

void copyMousePosition::Update(Agent *pAgent)
{
    pAgent->setPosition(sf::Vector2f(InputManager::getInstance()->getMousePosf()));
}