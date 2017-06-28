#include "Path.h"
#include "SFML\Graphics.hpp"
#include "Renderer.h"

std::string getPath();

Path::Path(sf::Font& newFont)
{
    m_font = newFont;
}

void Path::addNode(sf::Vector2f position)
{
    m_pathNodes.push_back(std::make_shared<PathNode>(position, m_font, nodeCount));
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

void Path::update(sf::Event& currentEvent)
{
    sf::Vector2f mousePos(sf::Mouse::getPosition(Renderer::getInstance()->getWindow()));
    for(unsigned int i = 0; i < m_pathNodes.size(); i++)
    {
        if (m_pathNodes[i].get()->getBounds().contains(mousePos))
        {
            m_pathNodes[i].get()->selected = true;
        }
        else
        {
            m_pathNodes[i].get()->selected = false;
        }
        m_pathNodes[i]->update();
    }
}

void Path::draw()
{
    for (std::vector<std::shared_ptr<PathNode>>::iterator iter = m_pathNodes.begin(); iter != m_pathNodes.end(); iter++)
    {
        iter->get()->draw();
    }
}