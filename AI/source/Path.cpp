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
    m_pathNodes.push_back(new PathNode(position, m_font, nodeCount));
    m_drawOrder.push_back(nodeCount);
    nodeCount++;
}

void Path::addEdge(PathNode* firstNode, PathNode* secondNode)
{
    Edge* newEdge = new Edge(firstNode, secondNode);
    firstNode->addEdge(newEdge);
    secondNode->addEdge(newEdge);
}

PathNode* Path::getNode(int index)
{
    return m_pathNodes[index];
}

void Path::update(sf::Event& currentEvent)
{
    sf::Vector2f mousePos(sf::Mouse::getPosition(Renderer::getInstance()->getWindow()));
    bool doneSwap = false;
    for (unsigned int i = 0; i < m_pathNodes.size(); i++)
    {
        m_pathNodes[i]->update();
        if (m_pathNodes[i]->getBounds().contains(mousePos))
        {
            if (currentEvent.type == sf::Event::EventType::MouseButtonPressed && currentEvent.mouseButton.button == sf::Mouse::Left && m_selectedPathNode == nullptr && doneSwap == false)
            {
                m_selectedPathNode = m_pathNodes[i];
                std::swap(m_drawOrder[i], m_drawOrder.back());
                doneSwap = true;
            }
            if (currentEvent.type == sf::Event::EventType::MouseButtonReleased && currentEvent.mouseButton.button == sf::Mouse::Left && m_selectedPathNode != nullptr)
            {
                m_selectedPathNode = nullptr;
            }
        }
        if (m_selectedPathNode != nullptr)
        {
            m_selectedPathNode->dragWithMouse(mousePos);
        }
    }
}

void Path::draw()
{
    for (std::vector<unsigned int>::iterator iter = m_drawOrder.begin(); iter != m_drawOrder.end(); iter++)
    {
        m_pathNodes[*iter]->draw();
    }
}