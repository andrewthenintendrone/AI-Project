#pragma once
#include "IBehavior.h"

class GameObject;

class Wander : public IBehavior
{
public:
    Wander(float maxVelocity = 300.0f, float wanderRadius = 50.0f, float wanderDistance = 200.0f, float wanderJitterAmount = 100.0f);
    virtual sf::Vector2f update();

private:
    float m_maxVelocity = 0.0f;
    float m_wanderRadius = 0.0f;
    float m_wanderDistance = 0.0f;
    float m_wanderJitterAmount = 0.0f;
};