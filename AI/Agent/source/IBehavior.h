#pragma once
#include "SFML\Graphics.hpp"

class Agent;

class IBehavior
{
public:
    IBehavior();
    virtual ~IBehavior() = 0;

    virtual sf::Vector2f update() = 0;
    Agent* m_myAgent = nullptr;
};