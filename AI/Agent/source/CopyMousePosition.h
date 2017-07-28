#pragma once
#include "IBehavior.h"

class copyMousePosition : public IBehavior
{
    virtual sf::Vector2f update();
};