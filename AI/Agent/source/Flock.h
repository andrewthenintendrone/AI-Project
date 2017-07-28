#pragma once
#include <vector>
#include "IBehavior.h"
#include "SFML\Graphics.hpp"
#include "GameObject.h"

class Flock : public IBehavior
{
public:
    Flock(GameObject* newTarget);
    virtual void update(Agent *pAgent);
protected:
    sf::Vector2f computeMovement(Agent* pAgent);
    sf::Vector2f computeAlignment(Agent* pAgent, std::vector<GameObject*> objects);
    sf::Vector2f computeCohesion(Agent* pAgent, std::vector<GameObject*> objects);
    sf::Vector2f computeSeperation(Agent* pAgent, std::vector<GameObject*> objects);
private:
    GameObject* m_target;
    float m_flockSpeed = 200.0f;

    float m_movementWeight = 0.08f;
    float m_alignmentWeight = 0.4f;
    float m_cohesionWeight = 0.3f;
    float m_seperationWeight = 0.7f;
};