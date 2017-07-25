#include "Path.h"
#include "SFML\Graphics.hpp"
#include "Renderer.h"
#include "InputManager.h"

std::string getPath();

Path::Path()
{
    m_gui.setPath(this);
}

PathNode* Path::addNode(sf::Vector2f position)
{
    m_pathNodes.push_back(new PathNode(position, m_pathNodes.size()));
    return m_pathNodes.back();
}

void Path::removeNode(PathNode* nodeToRemove)
{
    m_draggingNode = nullptr;
    m_pathNodes.remove(nodeToRemove);
    delete nodeToRemove;
}

void Path::addEdge(PathNode* firstNode, PathNode* secondNode)
{
    Edge* newEdge = new Edge(firstNode, secondNode);
    firstNode->addEdge(newEdge);
    secondNode->addEdge(newEdge);
}

PathNode* Path::getNode(int index)
{
    auto iter = m_pathNodes.begin();
    std::advance(iter, index);
    return (*iter);
}

PathNode* Path::getFirstNode()
{
    return m_pathNodes.front();
}

PathNode* Path::getLastNode()
{
    return m_pathNodes.back();
}

std::list<PathNode*>& Path::getPathNodes()
{
    return m_pathNodes;
}

void Path::update()
{
    m_selectedPathNode = nullptr;

    // store mouse position
    sf::Vector2f mousePos(sf::Mouse::getPosition(Renderer::getInstance()->getWindow()));

    // deal with dragging nodes
    for (auto iter = m_pathNodes.begin(); iter != m_pathNodes.end(); iter++)
    {
        if ((*iter)->getBounds().contains(mousePos))
        {
            m_selectedPathNode = (*iter);
            if (InputManager::getInstance()->getLeftHold() && m_draggingNode == nullptr)
            {
                m_draggingNode = (*iter);
            }
            else
            {
                m_draggingNode = nullptr;
            }
        }
        if (m_draggingNode != nullptr)
        {
            m_draggingNode->dragWithMouse(mousePos);
        }
        (*iter)->update((*iter) == m_selectedPathNode);
    }

    // deal with dropdown box
    if (InputManager::getInstance()->getRightClick())
    {
        m_gui.setPosition(mousePos);
        m_gui.isVisible = true;
    }
    if (InputManager::getInstance()->getLeftClick() && !m_gui.getBounds().contains(mousePos))
    {
        m_gui.isVisible = false;
    }
    if (m_gui.isVisible)
    {
        m_gui.update(m_selectedPathNode);
    }
}

void Path::draw()
{
    for(auto iter = m_pathNodes.begin(); iter != m_pathNodes.end(); iter++)
    {
        (*iter)->draw();
    }
    if (m_gui.isVisible)
    {
        m_gui.draw();
    }
}

void Path::resetNodeScores()
{
    for (auto iter = m_pathNodes.begin(); iter != m_pathNodes.end(); iter++)
    {
        (*iter)->setScores(this);
    }
}
