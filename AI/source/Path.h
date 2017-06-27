#pragma once
#include "PathNode.h"
#include <vector>
#include <memory>

class Path
{
public:
    Path();

    void addNode(sf::Vector2f position);
    void addEdge(std::shared_ptr<PathNode> firstNode, std::shared_ptr<PathNode> secondNode);
    std::shared_ptr<PathNode> getNode(int index);
    void draw();
private:
    std::vector<std::shared_ptr<PathNode>> m_pathNodes;
    unsigned int nodeCount = 0;
    sf::Text t_addNode;
};
