#pragma once
#include "IBehavior.h"

class CopyMousePosition : public IBehavior
{
    virtual sf::Vector2f update();
};