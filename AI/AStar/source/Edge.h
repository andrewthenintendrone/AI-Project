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
    float length();

    ~Edge();

    void recalculate();
    void draw();

private:
    sf::RectangleShape graphic;
    sf::Font m_font;
    sf::Text distanceText;
};