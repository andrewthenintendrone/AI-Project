#pragma once
#include "SFML\Graphics.hpp"

class PathNode;

class Edge
{
public:

    Edge(PathNode* newFirstNode, PathNode* newSecondNode);
    ~Edge();

    void setColor(sf::Color newColor);

    float m_length;
    void recalculate();
    void draw();

    // node pointers
    PathNode* m_firstNode = nullptr;
    PathNode* m_secondNode = nullptr;

    static const sf::Color YELLOW() { return sf::Color(255, 255, 0); }
    static const sf::Color BLUE() { return sf::Color(0, 0, 255); }

private:
    // graphic
    sf::RectangleShape m_line;
};