#pragma once
#include "IBehavior.h"

class GameObject;

class Flee : public IBehavior
{
public:
    Flee(GameObject* newTarget);
    Flee(GameObject* newTarget, float maxVelocity = 100.0f);
    virtual sf::Vector2f update();

private:
    GameObject* m_target;
    float m_maxVelocity = 0.0f;
};