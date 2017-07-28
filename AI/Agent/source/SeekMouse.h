#pragma once
#include "IBehavior.h"
#include "Agent.h"

class SeekMouse : public IBehavior
{
public:
    SeekMouse(float maxVelocity = 100.0f);
    virtual sf::Vector2f update();

private:
    float m_maxVelocity = 0.0f;
};