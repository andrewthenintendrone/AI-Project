#pragma once
#include "SFML\Graphics.hpp"
#include "Position.h"

class GridTile
{
public:

    GridTile();

    void setPosition(sf::Vector2f& newPosition);
    void setPosition(float newX, float newY);

    sf::RectangleShape getRectangleGraphic();
    sf::Vector2f getPosition();

    void draw(TILESTATE currentTileState);

private:
    sf::RectangleShape m_rectangleGraphic;
    sf::CircleShape m_circleGraphic;
};