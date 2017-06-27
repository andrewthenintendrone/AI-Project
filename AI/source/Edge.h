#pragma once
class PathNode;
#include "SFML\Graphics.hpp"

const sf::Color edgeColor = sf::Color(192, 80, 77);

class Edge
{
public:
    PathNode* firstNode;
    PathNode* secondNode;

    void draw();
};