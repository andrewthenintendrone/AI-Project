#pragma once
#include "SFML\Graphics.hpp"

class Agent;

// generic behaviour class
// a bevhavior includes
// a reference to the Agent it is part of
// an update function that returns a force
// a weighting that is used when multiple forces are being combined

class IBehavior
{
public:

    IBehavior();
    virtual ~IBehavior() = 0;

    virtual sf::Vector2f update() = 0;

    Agent* m_myAgent = nullptr;
    float m_weight = 0.0f;
};