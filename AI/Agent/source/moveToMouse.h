#pragma once
#include "IBehavior.h"
#include "Agent.h"

class moveToMouse : public IBehavior
{
public:
    virtual void Update(Agent* pAgent);

private:
    float m_maxVelocity = 500.0f;
};