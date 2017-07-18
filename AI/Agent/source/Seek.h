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
    float seekSpeed = 500.0f;
};