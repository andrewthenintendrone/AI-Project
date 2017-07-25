#pragma once
#include <SFML\Graphics.hpp>
#include "Edge.h"
#include "PathNode.h"

class Path;

enum class UIMODE {IDLE, ADDING, REMOVING, LINKING};

class UI2
{
public:
    UI2();

    void update(PathNode* selectedNode);
    void draw();
    void setPosition(sf::Vector2f newPosition);

private:
    sf::RectangleShape m_rightBar;

    sf::Texture m_addTex;
    sf::Sprite m_addSprite;

    sf::Texture m_removeTex;
    sf::Sprite m_removeSprite;

    sf::Texture m_linkTex;
    sf::Sprite m_linkSprite;

    UIMODE m_currentMode;
};