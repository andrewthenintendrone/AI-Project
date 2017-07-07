#pragma once
class PathNode;
#include "SFML\Graphics.hpp"

const sf::Color edgeColor = sf::Color(192, 80, 77);

class Edge
{
public:
    Edge(PathNode* newFirstNode, PathNode* newSecondNode);
    PathNode* firstNode;
    PathNode* secondNode;

    void recalculate();
    void draw();

private:
    sf::RectangleShape graphic;
};