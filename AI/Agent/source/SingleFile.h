#pragma once
#include "IBehavior.h"
#include <list>

class GameObject;

class SingleFile : public IBehavior
{
public:
    SingleFile(std::list<GameObject*>* flock, float maxVelocity = 150.0f, float slowRadius = 120.0f, float stopRadius = 20.0f);
    virtual sf::Vector2f update();

private:
    std::list<GameObject*>* m_flock;
    GameObject* m_target = nullptr;
    float m_maxVelocity = 0.0f;
    float m_slowRadius = 0.0f;
    float m_stopRadius = 0.0f;
};