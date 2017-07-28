#pragma once
#include "IBehavior.h"

class GameObject;

class Pursue : public IBehavior
{
public:
    Pursue(GameObject* newTarget, float maxVelocity = 100.0f);
    virtual sf::Vector2f update();

private:
    GameObject* m_target;
    float m_maxVelocity = 0.0f;
};