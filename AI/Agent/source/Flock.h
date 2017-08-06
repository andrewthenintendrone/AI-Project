#pragma once
#include <vector>
#include "IBehavior.h"
#include "SFML\Graphics.hpp"
#include "GameObject.h"

class Flock : public IBehavior
{
public:
    Flock(std::list<GameObject*>* flock, float maximumVelocity = 100.0f);
    virtual sf::Vector2f update();
protected:
    sf::Vector2f computeAlignment();
    sf::Vector2f computeCohesion(float radius);
private:
    std::list<GameObject*> m_flock;
    float m_maximumVelocity;

    float m_alignmentWeight = 0.5f;
    float m_cohesionWeight = 0.4f;
    float m_seperationWeight = 0.9f;

    float m_alignmentRadius = 200.0f;
    float m_cohesionRadius = 150.0f;
    float m_seperationRadius = 50.0f;
};