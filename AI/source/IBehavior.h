#pragma once
class Agent;

class IBehavior
{
public:
    IBehavior();
    virtual ~IBehavior() = 0;
    virtual void Update(Agent *pAgent) = 0;
};