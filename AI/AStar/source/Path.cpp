#include "Path.h"
#include "InputManager.h"
#include "Renderer.h"
#include "Edge.h"

// constructor
Path::Path()
{

}

// destructor
Path::~Path()
{

}

// update function
void Path::update()
{
    // update the UI
    m_ui.update();

    // update the path finder
    m_pathFinder.update();

    // process interaction from the user
    processInteraction();
}

// draw function
void Path::draw()
{
    for (std::list<PathNode*>::iterator iter = m_PathNodes.begin(); iter != m_PathNodes.end();)
    {
        // if there is a deleted node remove it from the list
        if ((*iter) == nullptr)
        {
            iter = m_PathNodes.erase(iter);
        }
        else
        {
            // draw the first path node in green
            if (*iter == m_PathNodes.front())
            {
                (*iter)->setColor(GREEN);
            }
            // draw the last path node in red
            else if (*iter == m_PathNodes.back())
            {
                (*iter)->setColor(RED);
            }
            // draw all other path nodes in purple
            else
            {
                (*iter)->setColor(PURPLE);
            }
            (*iter)->draw();
            iter++;
        }
    }

    // draw the ui
    m_ui.draw();

    // draw the path finder
    m_pathFinder.draw();
}

// process interaction from the user
void Path::processInteraction()
{
    // act differently based on the current UI mode
    switch (m_ui.getUImode())
    {
    case UIMODE::ADDING:
        addMode();
        break;
    case UIMODE::REMOVING:
        removeMode();
        break;
    case UIMODE::LINKING:
        linkMode();
        break;
    case UIMODE::IDLE:
        idleMode();
        break;
    default:
        break;
    }

    // prevent from "storing" link nodes between mode changes
    if (m_ui.getUImode() != UIMODE::LINKING)
    {
        m_firstLinkNode = nullptr;
        m_secondLinkNode = nullptr;
    }

    // if the space bar is pressed the pathfinder will seek to the goal node
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        // make sure there is more than 1 node
        if (m_PathNodes.size() > 1)
        {
            // reset all nodes
            resetNodes();

            // tell the path finder to seek from the first node to the last
            m_pathFinder.seekToGoal(m_PathNodes.front(), m_PathNodes.back());
        }
    }
}

// allow the user to add nodes
void Path::addMode()
{
    // the user is clicking the left mouse button
    if (InputManager::getInstance()->getLeftClick())
    {
        // ignore clicks on the UI
        if (InputManager::getInstance()->getMousePosf().x < Renderer::getInstance()->getWindowSizef().x - 200.0f)
        {
            // create a node at that position
            addNode(InputManager::getInstance()->getMousePosf());
        }
    }
}

// allow the user to remove nodes
void Path::removeMode()
{
    // the user is clicking the left mouse button
    if (InputManager::getInstance()->getLeftHold())
    {
        // ignore clicks on the UI
        if (InputManager::getInstance()->getMousePosf().x < Renderer::getInstance()->getWindowSizef().x - 200.0f)
        {
            for (std::list<PathNode*>::iterator iter = m_PathNodes.begin(); iter != m_PathNodes.end();)
            {
                // a node has been selected to remove
                if (InputManager::getInstance()->getHovering((*iter)->getGraphic()))
                {
                    // stop the pathfinder just in case
                    m_pathFinder.stopPathFinding();

                    // remove the node and all its edges
                    // this will also remove those edges from attached nodes
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

// allow the user to link nodes
void Path::linkMode()
{
    // the user is holding the left mouse button
    if (InputManager::getInstance()->getLeftHold())
    {
        for (std::list<PathNode*>::iterator iter = m_PathNodes.begin(); iter != m_PathNodes.end(); iter++)
        {
            // the user is hovering over a node
            if (InputManager::getInstance()->getHovering((*iter)->getGraphic()))
            {
                // there is no first link node
                // set the first link node to the current node
                if (m_firstLinkNode == nullptr)
                {
                    m_firstLinkNode = (*iter);
                }
                // the first link node has already been chosen
                // the current node is a different node
                // set the second link node to the current node
                else if (m_secondLinkNode == nullptr && (*iter) != m_firstLinkNode)
                {
                    m_secondLinkNode = (*iter);
                }
            }
        }
        // if both the first and second link nodes have been set
        if (m_firstLinkNode != nullptr && m_secondLinkNode != nullptr)
        {
            // check that the nodes are not already linked
            bool alreadyLinked = false;

            for (auto iter = m_firstLinkNode->getEdges()->begin(); iter != m_firstLinkNode->getEdges()->end(); iter++)
            {
                if ((*iter)->m_firstNode == m_firstLinkNode && (*iter)->m_secondNode == m_secondLinkNode)
                {
                    alreadyLinked = true;
                    break;
                }
                else if ((*iter)->m_secondNode == m_firstLinkNode && (*iter)->m_firstNode == m_secondLinkNode)
                {
                    alreadyLinked = true;
                    break;
                }
            }
            // if they are not already linked link them
            if (!alreadyLinked)
            {
                linkNodes(m_firstLinkNode, m_secondLinkNode);
            }

            // reset both link nodes back to nullptr
            m_firstLinkNode = nullptr;
            m_secondLinkNode = nullptr;
        }
    }
    // also reset both link nodes if the user releases the left mouse button
    else
    {
        m_firstLinkNode = nullptr;
        m_secondLinkNode = nullptr;
    }
}

// allow the user to drag nodes by default
void Path::idleMode()
{
    // if the user is holding down the left mouse button
    if (InputManager::getInstance()->getLeftHold())
    {
        // if a node is not already being dragged
        if (m_draggingNode == nullptr)
        {
            for (std::list<PathNode*>::iterator iter = m_PathNodes.begin(); iter != m_PathNodes.end(); iter++)
            {
                if (InputManager::getInstance()->getHovering((*iter)->getGraphic()))
                {
                    // keep track of the current node that is being dragged
                    m_draggingNode = (*iter);
                    break;
                }
            }
        }
        // the user iis in the process of dragging a node
        if (m_draggingNode != nullptr)
        {
            // set that nodes position to the position of the mouse
            m_draggingNode->setPosition(InputManager::getInstance()->getMousePosf());
        }
    }
    // the user is not holding down the left mouse button
    else
    {
        m_draggingNode = nullptr;
    }
}

// adds a new node
void Path::addNode(sf::Vector2f position)
{
    m_PathNodes.push_back(new PathNode(position));
}

// links two nodes with a new edge
void Path::linkNodes(PathNode* firstNode, PathNode* secondNode)
{
    // create a new edge connecting the two nodes
    Edge* newEdge = new Edge(firstNode, secondNode);

    // add the new edge to both nodes
    firstNode->addEdge(newEdge);
    secondNode->addEdge(newEdge);
}

// links the first and last nodes
void Path::linkNodes()
{
    linkNodes(m_PathNodes.front(), m_PathNodes.back());
}

// resets all nodes
void Path::resetNodes()
{
    for (auto iter = m_PathNodes.begin(); iter != m_PathNodes.end(); iter++)
    {
        (*iter)->reset();
    }
}
