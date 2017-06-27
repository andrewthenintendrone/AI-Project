#pragma once
#include "IBehavior.h"
#include "TimeManager.h"

class moveToMouse : public IBehavior
{
public:
    virtual void Update(Agent* pAgent);

private:
    sf::Vector2f m_mousePosition;
};