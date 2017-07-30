#pragma once
#include "IBehavior.h"
#include <list>

class Wall;

class Avoid : public IBehavior
{
public:
    Avoid(std::list<Wall*>& walls, float maximimumVelocity = 500, float feelerDistance = 10);
    ~Avoid();

    virtual sf::Vector2f update();
private:
    float m_maximumVelocity;
    float m_feelerDistance;

    std::list<Wall*> m_walls;
};