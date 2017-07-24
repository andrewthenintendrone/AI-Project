#pragma once
#include "IBehavior.h"
#include "GameObject.h"

class Flee : public IBehavior
{
public:
    Flee(GameObject* newTarget);
    virtual void Update(Agent *pAgent);

private:
    GameObject* m_target;
    float m_mass = 1.0f;
    float m_maxVelocity = 50.0f;
    float m_maxForce = 60.0f;
    float m_maxSpeed = 500.0f;
};