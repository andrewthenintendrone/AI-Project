#pragma once
#include "IBehavior.h"

class WrapScreen : public IBehavior
{
public:
    WrapScreen();

    virtual sf::Vector2f update();
private:
    sf::Vector2f m_windowSize;
};