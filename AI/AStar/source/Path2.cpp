#include "Path2.h"
#include "InputManager.h"
#include "Renderer.h"
#include "Edge2.h"


Path2::Path2()
{

}

Path2::~Path2()
{

}

void Path2::update()
{
    m_ui.update();
    processInteraction();
}

void Path2::draw()
{
    for (std::list<PathNode2*>::iterator iter = m_PathNodes.begin(); iter != m_PathNodes.end(); iter++)
    {
        (*iter)->draw();
    }
    m_ui.draw();
}

void Path2::processInteraction()
{
    // UI is in add mode
    if (m_ui.getUImode() == UIMODE::ADDING)
    {
        m_firstLinkNode = nullptr;
        m_secondLinkNode = nullptr;
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
        m_firstLinkNode = nullptr;
        m_secondLinkNode = nullptr;

        // we are clicking left of the UI
        if (InputManager::getInstance()->getLeftClick())
        {
            if (InputManager::getInstance()->getMousePosf().x < Renderer::getInstance()->getWindowSizef().x - 200.0f)
            {
                for (std::list<PathNode2*>::iterator iter = m_PathNodes.begin(); iter != m_PathNodes.end();)
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
        // we are clicking
        if (InputManager::getInstance()->getLeftClick())
        {
            for (std::list<PathNode2*>::iterator iter = m_PathNodes.begin(); iter != m_PathNodes.end(); iter++)
            {
                if (InputManager::getInstance()->getHovering((*iter)->getGraphic()))
                {
                    if (m_firstLinkNode == nullptr)
                    {
                        m_firstLinkNode = (*iter);
                        break;
                    }
                    if (m_secondLinkNode == nullptr && (*iter) != m_firstLinkNode)
                    {
                        m_secondLinkNode = (*iter);
                        break;
                    }
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

void Path2::addNode(sf::Vector2f position)
{
    m_PathNodes.push_back(new PathNode2(position));
}

void Path2::removeNode(PathNode2* nodeToRemove)
{
    m_PathNodes.remove(nodeToRemove);
}

void Path2::linkNodes(PathNode2* firstNode, PathNode2* secondNode)
{
    Edge2* newEdge = new Edge2(firstNode, secondNode);
    firstNode->addEdge(newEdge);
    secondNode->addEdge(newEdge);
}
