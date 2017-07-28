#pragma once
#include "IBehavior.h"
#include "Agent.h"

class moveToMouse : public IBehavior
{
public:
    moveToMouse();
    moveToMouse(float maxVelocity);
    virtual sf::Vector2f update();

private:
    float m_maxVelocity = 500.0f;
};