#pragma once
#include "SFML\Graphics.hpp"
#include <list>
#include <vector>

class GameObject;
class IBehavior;

class Agent
{
public:
    // constructor / destructor
    Agent(GameObject* parent);
    ~Agent();

    // access behaviors
    void addBehaviour (IBehavior* newBehavior);
    void removeBehavior();

    // access velocity
    sf::Vector2f getVelocity();
    void setVelocity(sf::Vector2f newVelocity);
    void addVelocity(sf::Vector2f velocityToAdd);

    // access position
    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f newPosition);

    // access rotation
    float getRotation();
    void setRotation(float newRotation);

    // access parent pointer
    GameObject* getParentPointer();

    void update();

protected:

    GameObject* m_parentPointer;

    std::list<IBehavior*> m_behaviours;

    sf::Vector2f m_position;
    sf::Vector2f m_velocity;

    float m_maxSpeed = 500.0f;
    float m_rotation = 0.0f;

    void sense();
    void think();
    void act();
};