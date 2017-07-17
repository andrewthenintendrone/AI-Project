#pragma once
#include "PathNode.h"
#include "UI.h"
#include <vector>

class Path
{
public:
    Path();

    void addNode(sf::Vector2f position);
    void addEdge(PathNode* firstNode, PathNode* secondNode);
    PathNode* getNode(int index);
    void update(sf::Event currentEvent);
    void draw();
private:
    std::vector<PathNode*> m_pathNodes;
    unsigned int nodeCount = 0;
    sf::Font m_font;
    sf::Text t_addNode;
    PathNode* m_draggingNode = nullptr;
    PathNode* m_selectedPathNode = nullptr;
    UI m_gui;
};
