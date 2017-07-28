#pragma once
#include <string>
#include "SFML\Graphics.hpp"
#include "Agent.h"

class GameObject
{
public:
    GameObject();
    GameObject(std::string fileName);
    ~GameObject();

    GameObject* setSprite(std::string fileName);
    sf::Sprite* getSprite();

    GameObject* setText(std::string& newText, sf::Font& newFont);
    sf::Text* getText();

    Agent* getAgent();

    void update();
    void draw();

    void addBehavior(IBehavior* newBehavior);
protected:
    sf::Texture* m_texture = nullptr;
    sf::Sprite* m_sprite = nullptr;
    sf::Text* m_text = nullptr;
    Agent* m_agent = nullptr;
};