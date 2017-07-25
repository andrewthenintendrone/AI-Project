#pragma once
#include "SFML\Graphics.hpp"
#include <list>
#include "Edge.h"
#include <limits>

class PathNode2
{
public:
    PathNode2(sf::Vector2f newPosition);
    ~PathNode2();

    void draw();
private:
    sf::CircleShape m_graphic;

    std::list<PathNode2*> m_neighbors;
};