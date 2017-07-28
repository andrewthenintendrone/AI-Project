#pragma once
#include "IBehavior.h"

class keyBoardControl : public IBehavior
{
public:
    keyBoardControl(float maxVelocity = 100.0f);

    virtual sf::Vector2f update();
private:
    float m_maxVelocity = 0.0f;
};