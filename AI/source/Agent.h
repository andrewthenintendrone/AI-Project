#pragma once
#include <list>
#include "IBehavior.h"
#include "TimeManager.h"
class GameObject;

class Agent
{
public:
    Agent(GameObject* parent);
    ~Agent();

    void addBehaviour (IBehavior* newBehavior);

    void Update();

    void setVelocity(sf::Vector2f newVelocity);
    sf::Vector2f getVelocity();
    void addVelocity(sf::Vector2f velocityToAdd);

    void setPosition(sf::Vector2f newPosition);
    sf::Vector2f getPosition();

    void setRotation(float newRotation);
    float getRotation();

    void pushBehaviour(IBehavior* newBehavior);

    GameObject* getParentPointer();
protected:
    std::list<IBehavior*> m_behaviours;
    sf::Vector2f m_velocity;
    sf::Vector2f m_position;
    float m_rotation = 0;
    GameObject* m_parentPointer;
};