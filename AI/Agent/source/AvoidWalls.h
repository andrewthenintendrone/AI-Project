#pragma once
#include "IBehavior.h"
#include <list>

class Wall;

class AvoidWalls : public IBehavior
{
public:
    AvoidWalls(std::list<Wall*>& walls, float maximimumVelocity = 500, float feelerDistance = 10);
    ~AvoidWalls();

    virtual sf::Vector2f update();
private:
    float m_maximumVelocity;
    float m_feelerDistance;

    std::list<Wall*> m_walls;
};