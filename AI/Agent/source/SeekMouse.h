#pragma once
#include "IBehavior.h"
#include "Agent.h"

class SeekMouse : public IBehavior
{
public:
    SeekMouse(float maxVelocity = 150.0f, float slowRadius = 120.0f, float stopRadius = 20.0f);
    virtual sf::Vector2f update();

private:
    float m_maxVelocity = 0.0f;
    float m_slowRadius = 0.0f;
    float m_stopRadius = 0.0f;
};