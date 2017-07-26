#pragma once
#include "PathNode2.h"
#include "UI2.h"

class PathNode2;

class Path2
{
public:
    Path2();
    ~Path2();

    void update();
    void draw();

    void processInteraction();
    void addNode(sf::Vector2f position);
    void removeNode(PathNode2* nodeToRemove);
    void linkNodes(PathNode2* firstNode, PathNode2* secondNode);

private:
    std::list<PathNode2*> m_PathNodes;

    PathNode2* m_firstLinkNode = nullptr;
    PathNode2* m_secondLinkNode = nullptr;
    UI2 m_ui;
};