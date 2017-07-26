#include "Path.h"
#include "InputManager.h"
#include "Renderer.h"
#include "Edge.h"


Path::Path()
{

}

Path::~Path()
{

}

void Path::update()
{
    m_ui.update();
    processInteraction();
}

void Path::draw()
{
    for (std::list<PathNode*>::iterator iter = m_PathNodes.begin(); iter != m_PathNodes.end(); iter++)
    {
        (*iter)->draw();
    }
    m_ui.draw();
}

void Path::processInteraction()
{
    // UI is in add mode
    if (m_ui.getUImode() == UIMODE::ADDING)
    {
        // we are clicking left of the UI
        if (InputManager::getInstance()->getLeftClick())
        {
            if (InputManager::getInstance()->getMousePosf().x < Renderer::getInstance()->getWindowSizef().x - 200.0f)
            {
                addNode(InputManager::getInstance()->getMousePosf());
            }
        }
    }
    else if (m_ui.getUImode() == UIMODE::REMOVING)
    {
        // we are clicking left of the UI
        if (InputManager::getInstance()->getLeftClick())
        {
            if (InputManager::getInstance()->getMousePosf().x < Renderer::getInstance()->getWindowSizef().x - 200.0f)
            {
                for (std::list<PathNode*>::iterator iter = m_PathNodes.begin(); iter != m_PathNodes.end();)
                {
                    if (InputManager::getInstance()->getHovering((*iter)->getGraphic()))
                    {
                        m_PathNodes.erase(iter++);
                    }
                    else
                    {
                        iter++;
                    }
                }
            }
        }
    }
    else if (m_ui.getUImode() == UIMODE::LINKING)
    {
        // we are holding left of the UI
        if (InputManager::getInstance()->getLeftClick())
        {
            for (std::list<PathNode*>::iterator iter = m_PathNodes.begin(); iter != m_PathNodes.end();)
            {
                if (InputManager::getInstance()->getHovering((*iter)->getGraphic()))
                {
                    if (m_firstLinkNode == nullptr)
                    {
                        m_firstLinkNode = (*iter);
                    }
                    else if (m_secondLinkNode == nullptr && m_secondLinkNode != m_firstLinkNode)
                    {
                        m_secondLinkNode = (*iter);
                    }
                }
            }
            if (m_firstLinkNode != nullptr && m_secondLinkNode != nullptr)
            {
                linkNodes(m_firstLinkNode, m_secondLinkNode);
                m_firstLinkNode = nullptr;
                m_secondLinkNode = nullptr;
            }
        }
    }
}

void Path::addNode(sf::Vector2f position)
{
    m_PathNodes.push_back(new PathNode(position));
}

void Path::removeNode(PathNode* nodeToRemove)
{
    m_PathNodes.remove(nodeToRemove);
}

void Path::linkNodes(PathNode* firstNode, PathNode* secondNode)
{
    Edge* newEdge = new Edge(firstNode, secondNode);
    firstNode->addEdge(newEdge);
    secondNode->addEdge(newEdge);
}
