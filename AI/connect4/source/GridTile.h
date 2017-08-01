#pragma once
#include "SFML\Graphics.hpp"

enum class TILESTATE { EMPTY, RED, YELLOW };

class GridTile
{
public:

    GridTile();

    void setPosition(sf::Vector2f& newPosition);
    void setPosition(float newX, float newY);

    sf::Vector2f getPosition();

    TILESTATE getState();
    void setState(TILESTATE newState);

    void update();
    void draw();

private:
    TILESTATE m_tileState = TILESTATE::EMPTY;
    sf::RectangleShape m_rectangleGraphic;
    sf::CircleShape m_circleGraphic;
};