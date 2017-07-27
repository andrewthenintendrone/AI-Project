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
    for (std::list<PathNode*>::iterator iter = m_PathNodes.begin(); iter != m_PathNodes.end();)
    {
        if ((*iter) == nullptr)
        {
            iter = m_PathNodes.erase(iter);
        }
        else
        {
            (*iter)->draw();
            iter++;
        }
    }
    m_ui.draw();
}

void Path::processInteraction()
{
    // add mode
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
    // remove mode
    else if (m_ui.getUImode() == UIMODE::REMOVING)
    {
        // we are clicking left of the UI
        if (InputManager::getInstance()->getLeftHold())
        {
            if (InputManager::getInstance()->getMousePosf().x < Renderer::getInstance()->getWindowSizef().x - 200.0f)
            {
                for (std::list<PathNode*>::iterator iter = m_PathNodes.begin(); iter != m_PathNodes.end();)
                {
                    if (InputManager::getInstance()->getHovering((*iter)->getGraphic()))
                    {
                        (*iter)->deleteEdges();
                        delete(*iter);
                        (*iter) = nullptr;
                        iter = m_PathNodes.erase(iter);
                    }
                    else
                    {
                        iter++;
                    }
                }
            }
        }
    }
    // link mode
    else if (m_ui.getUImode() == UIMODE::LINKING)
    {
        // we are holding left of the UI
        if (InputManager::getInstance()->getLeftHold())
        {
            for (std::list<PathNode*>::iterator iter = m_PathNodes.begin(); iter != m_PathNodes.end(); iter++)
            {
                if (InputManager::getInstance()->getHovering((*iter)->getGraphic()))
                {
                    if (m_firstLinkNode == nullptr)
                    {
                        m_firstLinkNode = (*iter);
                    }
                    else if (m_secondLinkNode == nullptr && (*iter) != m_firstLinkNode)
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
        else
        {
            m_firstLinkNode = nullptr;
            m_secondLinkNode = nullptr;
        }
    }
    // idle mode
    else
    {
        if (InputManager::getInstance()->getLeftHold())
        {
            if (m_draggingNode == nullptr)
            {
                for (std::list<PathNode*>::iterator iter = m_PathNodes.begin(); iter != m_PathNodes.end(); iter++)
                {
                    if (InputManager::getInstance()->getHovering((*iter)->getGraphic()))
                    {
                        m_draggingNode = (*iter);
                        break;
                    }
                }
            }
            if (m_draggingNode != nullptr)
            {
                m_draggingNode->setPosition(InputManager::getInstance()->getMousePosf());
            }
        }
        else
        {
            m_draggingNode = nullptr;
        }
    }

    // prevent from "storing" link nodes between mode changes
    if (m_ui.getUImode() != UIMODE::LINKING)
    {
        m_firstLinkNode = nullptr;
        m_secondLinkNode = nullptr;
    }
}

void Path::addNode(sf::Vector2f position)
{
    m_PathNodes.push_back(new PathNode(position));
}

void Path::removeNode(PathNode* nodeToRemove)
{
    m_PathNodes.remove(nodeToRemove);
    delete nodeToRemove;
    nodeToRemove = nullptr;
}

void Path::linkNodes(PathNode* firstNode, PathNode* secondNode)
{
    Edge* newEdge = new Edge(firstNode, secondNode);
    firstNode->addEdge(newEdge);
    secondNode->addEdge(newEdge);
}

void Path::linkNodes()
{
    linkNodes(m_PathNodes.front(), m_PathNodes.back());
}