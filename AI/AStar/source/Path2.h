#pragma once
#include "PathNode2.h"
#include "UI2.h"

class Path2
{
public:
    Path2();
    ~Path2();

    void update();
    void draw();

    void addNode(sf::Vector2f position);
    void removeNode(PathNode2* nodeToRemove);

private:
    std::list<PathNode2*> m_PathNodes;
    UI2 m_ui;
};