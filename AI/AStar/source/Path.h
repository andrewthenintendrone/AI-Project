#pragma once
#include "PathNode.h"
#include "UI.h"
#include "PathFinder.h"

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
    void linkNodes(PathNode* firstNode, PathNode* secondNode);
    void linkNodes();

    void resetNodes();

private:
    std::list<PathNode*> m_PathNodes;
    PathNode* m_draggingNode = nullptr;

    PathNode* m_firstLinkNode = nullptr;
    PathNode* m_secondLinkNode = nullptr;
    UI m_ui;

    PathFinder m_pathFinder;
};