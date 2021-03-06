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
    void addBehaviour (IBehavior* newBehavior, float newWeight = 1.0f);
    void removeBehavior();

    // access velocity
    sf::Vector2f getVelocity();
    void setVelocity(sf::Vector2f newVelocity);
    void addVelocity(sf::Vector2f velocityToAdd);

    // access position
    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f newPosition);

    // access parent pointer
    GameObject* getParentPointer();

    // update function
    void update();

protected:

    // reference to the GameObject it is attached to
    GameObject* m_parentPointer;

    // list of behaviours
    std::list<IBehavior*> m_behaviours;

    // position and velocity
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;

    // maximum speed
    float m_maxSpeed = 500.0f;

    void sense();
    void think();
    void act();
};