#pragma once
#include "PathNode.h"
#include <vector>

class Path
{
public:
    Path(sf::Font& newFont);

    void addNode(sf::Vector2f position);
    void addEdge(PathNode* firstNode, PathNode* secondNode);
    PathNode* getNode(int index);
    void update(sf::Event& currentEvent);
    void draw();
private:
    std::vector<PathNode*> m_pathNodes;
    std::vector<unsigned int> m_drawOrder;
    unsigned int nodeCount = 0;
    sf::Font m_font;
    sf::Text t_addNode;
    PathNode* m_selectedPathNode = nullptr;
};
