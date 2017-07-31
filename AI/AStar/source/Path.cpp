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
    m_pathFinder.update();
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
            if (*iter == m_PathNodes.front())
            {
                (*iter)->setColor(sf::Color::Green);
            }
            else if (*iter == m_PathNodes.back())
            {
                (*iter)->setColor(sf::Color::Red);
            }
            else
            {
                (*iter)->setColor(sf::Color(128, 0, 255));
            }
            (*iter)->draw();
            iter++;
        }
    }
    m_ui.draw();
    m_pathFinder.draw();
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
                        // fix up pathfinder
                        m_pathFinder.stopPathFinding();

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

    // if the a button is pressed the pathfinder will seek to the goal node
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if (m_PathNodes.size() > 1)
        {
            resetNodes();
            m_pathFinder.seekToGoal(m_PathNodes.front(), m_PathNodes.back());
        }
    }
}

void Path::addNode(sf::Vector2f position)
{
    m_PathNodes.push_back(new PathNode(position));
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

void Path::resetNodes()
{
    for (auto iter = m_PathNodes.begin(); iter != m_PathNodes.end(); iter++)
    {
        (*iter)->reset();
        for (auto iter2 = (*iter)->getEdges()->begin(); iter2 != (*iter)->getEdges()->end(); iter2++)
        {
            (*iter2)->setColor(sf::Color(255, 255, 0));
        }
    }
}
