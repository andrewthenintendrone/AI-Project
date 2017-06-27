#pragma once
#include "IBehavior.h"
#include "GameObject.h"

class Flock : public IBehavior
{
public:
    Flock(GameObject* newTarget);
    virtual void Update(Agent *pAgent);
protected:
    sf::Vector2f computeMovement(Agent* pAgent);
    sf::Vector2f computeAlignment(Agent* pAgent, std::vector<GameObject*> objects);
    sf::Vector2f computeCohesion(Agent* pAgent, std::vector<GameObject*> objects);
    sf::Vector2f computeSeperation(Agent* pAgent, std::vector<GameObject*> objects);
private:
    GameObject* m_target;
    float m_flockSpeed = 200;
};