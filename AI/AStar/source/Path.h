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

    void addMode();
    void removeMode();
    void linkMode();
    void idleMode();

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

    const sf::Color GREEN = sf::Color(0, 255, 0);
    const sf::Color RED = sf::Color(255, 0, 0);
    const sf::Color PURPLE = sf::Color(128, 0, 255);
};