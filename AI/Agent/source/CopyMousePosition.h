#pragma once
#include "IBehavior.h"

class copyMousePosition : public IBehavior
{
    virtual void update(Agent *pAgent);
};