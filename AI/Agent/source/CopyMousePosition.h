#pragma once
#include "IBehavior.h"

class copyMousePosition : public IBehavior
{
    virtual void Update(Agent *pAgent);
};