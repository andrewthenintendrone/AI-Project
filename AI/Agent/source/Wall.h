#pragma once
#include "SFML\Graphics.hpp"

class Wall
{
public:
    Wall(float width = 100, float height = 100);
    ~Wall();

    sf::Vector2f getPosition();
    sf::FloatRect getBounds();
    void draw();

private:
    sf::RectangleShape m_wallGraphic;
};