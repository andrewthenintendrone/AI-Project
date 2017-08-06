#pragma once
#include <SFML\Graphics.hpp>

class Path;

// enum of UI states
enum class UIMODE {IDLE, ADDING, REMOVING, LINKING};

class UI
{
public:

    UI();

    void update();
    void draw();

    void setPosition(sf::Vector2f newPosition);

    UIMODE getUImode();

private:

    // graphics
    sf::RectangleShape m_rightBar;

    sf::Texture m_addTex;
    sf::Sprite m_addSprite;

    sf::Texture m_removeTex;
    sf::Sprite m_removeSprite;

    sf::Texture m_linkTex;
    sf::Sprite m_linkSprite;

    // keep track of the UI state
    UIMODE m_currentMode = UIMODE::IDLE;
    void updateUIState();

    // used for scaling
    sf::Vector2u windowSize;
    float iconSize = 100;
    float barWidth = 200;
};