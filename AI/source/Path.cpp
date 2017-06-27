#include "Path.h"
#include "SFML\Graphics.hpp"

std::string getPath();

Path::Path()
{

}

void Path::addNode(sf::Vector2f position)
{
    m_pathNodes.push_back(std::make_shared<PathNode>(position, nodeCount));
    nodeCount++;
}

void Path::addEdge(std::shared_ptr<PathNode> firstNode, std::shared_ptr<PathNode> secondNode)
{
    std::shared_ptr<Edge> newEdge = std::make_shared<Edge>(firstNode, secondNode);
    firstNode->addEdge(newEdge);
    secondNode->addEdge(newEdge);
}

std::shared_ptr<PathNode> Path::getNode(int index)
{
    return m_pathNodes[index];
}

void Path::draw()
{
    for(std::vector<std::shared_ptr<PathNode>>::iterator iter = m_pathNodes.begin(); iter != m_pathNodes.end(); iter++)
    {
        iter->get()->draw();
    }
    
}