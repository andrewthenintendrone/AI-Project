#pragma once
#include "SFML\Graphics.hpp"

class PathNode;

class Edge
{
public:
    Edge(PathNode* newFirstNode, PathNode* newSecondNode);
    ~Edge();

    // node pointers
    PathNode* m_firstNode = nullptr;
    PathNode* m_secondNode = nullptr;

    void setColor(sf::Color newColor);

    float m_length;
    void recalculate();
    void draw();

private:
    // graphic
    sf::RectangleShape m_line;
};