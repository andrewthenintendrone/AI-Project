#include "Path.h"
#include "SFML\Graphics.hpp"
#include "Renderer.h"

std::string getPath();

Path::Path()
{
    m_gui.setPath(this);
    m_font.loadFromFile(getPath() + "\\resources\\font\\calibri.ttf");
}

void Path::addNode(sf::Vector2f position)
{
    m_pathNodes.push_back(new PathNode(position, m_font, nodeCount));
    nodeCount++;
}

void Path::removeNode(PathNode* nodeToRemove)
{
    nodeToRemove->remove();
    m_pathNodes.remove(nodeToRemove);
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

void Path::update(sf::Event currentEvent)
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
            if (currentEvent.type == sf::Event::EventType::MouseButtonPressed && currentEvent.mouseButton.button == sf::Mouse::Left && m_draggingNode == nullptr)
            {
                m_draggingNode = (*iter);
            }
            if (currentEvent.type == sf::Event::EventType::MouseButtonReleased && currentEvent.mouseButton.button == sf::Mouse::Left && m_draggingNode != nullptr)
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
    if (currentEvent.type == sf::Event::EventType::MouseButtonPressed && currentEvent.mouseButton.button == sf::Mouse::Right)
    {
        m_gui.setPosition(mousePos);
        m_gui.isVisible = true;
    }
    if (currentEvent.type == sf::Event::EventType::MouseButtonPressed && currentEvent.mouseButton.button == sf::Mouse::Left && !m_gui.getBounds().contains(mousePos))
    {
        m_gui.isVisible = false;
    }
    if (m_gui.isVisible)
    {
        m_gui.update(m_selectedPathNode, currentEvent.type == sf::Event::EventType::MouseButtonPressed && currentEvent.mouseButton.button == sf::Mouse::Left);
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