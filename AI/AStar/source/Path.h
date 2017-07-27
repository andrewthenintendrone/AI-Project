#pragma once
#include "PathNode.h"
#include "UI.h"

class PathNode;

class Path
{
public:
    Path();
    ~Path();

    void update();
    void draw();

    void processInteraction();
    void addNode(sf::Vector2f position);
    void removeNode(PathNode* nodeToRemove);
    void linkNodes(PathNode* firstNode, PathNode* secondNode);
    void linkNodes();

private:
    std::list<PathNode*> m_PathNodes;

    PathNode* m_firstLinkNode = nullptr;
    PathNode* m_secondLinkNode = nullptr;
    UI m_ui;
};