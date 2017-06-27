#pragma once
#include "SFML\Graphics.hpp"
#include "Agent.h"
#include "moveToMouse.h"

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
    void Update();
    void Draw();

    void addBehavior(IBehavior* newBehavior);
private:
    sf::Texture* m_texture;
    sf::Sprite* m_sprite;
    sf::Text* m_text;
    Agent* m_agent;
};