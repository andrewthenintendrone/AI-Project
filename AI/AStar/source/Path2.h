#pragma once
#include "PathNode2.h"

class Path2
{
public:
    Path2();
    ~Path2();

    void addNode(sf::Vector2f position);
    void removeNode(PathNode2* nodeToRemove);

private:
    std::list<PathNode2> m_PathNodes;
};