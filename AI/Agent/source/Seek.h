#pragma once
#include "IBehavior.h"
#include "GameObject.h"

class Seek : public IBehavior
{
public:
    Seek(GameObject* newTarget);
    virtual void Update(Agent *pAgent);

private:
    GameObject* m_target;
    float m_mass = 1.0f;
    float m_slowingRange = 150.0f;
    float m_maxVelocity = 500.0f;
    float m_maxForce = 60.0f;
    float m_maxSpeed = 500.0f;
};