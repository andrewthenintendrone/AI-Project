#pragma once
#include "PathNode.h"
#include "UI.h"
#include <list>

class Path
{
public:
    Path();

    PathNode* addNode(sf::Vector2f position);
    void removeNode(PathNode* nodeToremove);
    void addEdge(PathNode* firstNode, PathNode* secondNode);
    PathNode* getNode(int index);
    PathNode* getFirstNode();
    PathNode* getLastNode();
    std::list<PathNode*>& getPathNodes();
    void update();
    void draw();

    void resetNodeScores();
private:
    std::list<PathNode*> m_pathNodes;
    sf::Text t_addNode;
    PathNode* m_draggingNode = nullptr;
    PathNode* m_selectedPathNode = nullptr;
    UI m_gui;
};
