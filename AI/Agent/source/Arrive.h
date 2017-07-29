#pragma once
#include "IBehavior.h"

class GameObject;

class Arrive : public IBehavior
{
public:
    Arrive(GameObject* newTarget, float maxVelocity = 100.0f, float slowRadius = 120.0f, float stopRadius = 20.0f);
    virtual sf::Vector2f update();

private:
    GameObject* m_target;
    float m_maxVelocity = 0.0f;
    float m_slowRadius = 0.0f;
    float m_stopRadius = 0.0f;
};