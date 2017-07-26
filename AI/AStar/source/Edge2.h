#pragma once
#include "SFML\Graphics.hpp"

class PathNode2;

class Edge2
{
public:
    Edge2(PathNode2* newFirstNode, PathNode2* newSecondNode);
    ~Edge2();

    void recalculate();
    void draw();

private:
    // graphic
    sf::RectangleShape m_line;

    // node pointers
    PathNode2* m_firstNode = nullptr;
    PathNode2* m_secondNode = nullptr;

};