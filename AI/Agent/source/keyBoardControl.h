#pragma once
#include "IBehavior.h"

class KeyboardControl : public IBehavior
{
public:
    KeyboardControl(float maxVelocity = 100.0f);

    virtual sf::Vector2f update();
private:
    float m_maxVelocity = 0.0f;
};