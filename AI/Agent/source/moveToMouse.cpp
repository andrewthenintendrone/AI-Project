#include "moveToMouse.h"
#include "Renderer.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Agent.h"

void moveToMouse::Update(Agent* pAgent)
{
    m_mousePosition = sf::Vector2f((float)sf::Mouse::getPosition(Renderer::getInstance()->getWindow()).x, (float)sf::Mouse::getPosition(Renderer::getInstance()->getWindow()).y);
    sf::Vector2f direction = (m_mousePosition - pAgent->getPosition());
    float magnitude = sqrtf((direction.x * direction.x) + (direction.y * direction.y));

    if (magnitude >= 32)
    {
        pAgent->setVelocity(direction / magnitude * 500.0f);
        float rotation = atan2(-direction.y, -direction.x) * 180 / (float)M_PI;
        pAgent->setRotation(rotation);
    }
    else
    {
        pAgent->setVelocity(sf::Vector2f(0, 0));
    }
}