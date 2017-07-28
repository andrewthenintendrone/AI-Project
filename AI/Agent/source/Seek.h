#pragma once
#include "IBehavior.h"
#include "GameObject.h"

class Seek : public IBehavior
{
public:
    Seek(GameObject* newTarget);
    Seek(GameObject* newTarget, float maxVelocity);
    virtual sf::Vector2f update();

private:
    GameObject* m_target;
    float m_mass = 1.0f;
    float m_slowingRange = 150.0f;
    float m_maxVelocity = 100.0f;
};