#pragma once
#include <string>
#include "SFML\Graphics.hpp"
#include "Agent.h"

class GameObject
{
public:

    // construtors / destructors
    GameObject();
    GameObject(std::string fileName);
    ~GameObject();

    // access to sprite
    sf::Sprite* getSprite();
    GameObject* setSprite(std::string fileName);


    // access to Agent
    Agent* getAgent();

    // update and draw functions
    void update();
    void draw();

    // access to behaviours
    void addBehavior(IBehavior* newBehavior, float newWeight = 1.0f);
    void removeBehavior();

protected:

    // graphics
    sf::Texture* m_texture = nullptr;
    sf::Sprite* m_sprite = nullptr;

    // Agent
    Agent* m_agent = nullptr;
};