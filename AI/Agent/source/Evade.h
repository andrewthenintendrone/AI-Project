#pragma once
#include "IBehavior.h"

class GameObject;

class Evade : public IBehavior
{
public:
    Evade(GameObject* newTarget, float maxVelocity = 100.0f, float arriveRange = 150.0f, float mass = 1.0f);
    virtual sf::Vector2f update();

private:
    GameObject* m_target;
    float m_maxVelocity = 0.0f;
    float m_slowingRange = 0.0f;
    float m_mass = 0.0f;
};