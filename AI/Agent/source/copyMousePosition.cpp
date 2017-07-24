#include "CopyMousePosition.h"
#include "Renderer.h"
#include "Agent.h"

void copyMousePosition::Update(Agent *pAgent)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(Renderer::getInstance()->getWindow());
    pAgent->setPosition(sf::Vector2f(mousePos.x, mousePos.y));
}