#pragma once
#include "IBehavior.h"
#include "GameObject.h"

class keyBoardControl : public IBehavior
{
public:
    virtual void Update(Agent* pAgent);
private:
    float moveSpeed = 500.0f;
};