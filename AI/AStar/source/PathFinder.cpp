#include "PathFinder.h"
#include "Renderer.h"
#include "Edge.h"
#include "VectorMaths.h"
#include <algorithm>

std::string getPath();

PathFinder::PathFinder(PathNode* start, PathNode* goal)
{
    m_startNode = start;
    m_goalNode = goal;

    m_texture = new sf::Texture;
    m_texture->loadFromFile(getPath() + "\\resources\\graphics\\PathFinder.png");
    m_sprite = new sf::Sprite;
    m_sprite->setTexture(*m_texture);

    m_sprite->setOrigin(sf::Vector2f(m_sprite->getGlobalBounds().width / 2.0f, m_sprite->getGlobalBounds().height / 2.0f));
}

PathFinder::~PathFinder()
{
    delete m_sprite;
    delete m_texture;
}

void PathFinder::Update()
{
    Renderer::getInstance()->Draw(m_sprite);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::B))
    {
        std::list<PathNode*> shortestPath = AStar();
    }
}

// uses AStar to find the shortest path
std::list<PathNode*> PathFinder::AStar()
{
    m_closedSet.clear();
    m_openSet.clear();

    m_startNode->setGscore(0);
    m_startNode->setFscore(magnitude(m_goalNode->getPosition() - m_startNode->getPosition()));
    m_openSet.push_back(m_startNode);

    while (!m_openSet.empty())
    {
        for (auto iter = m_openSet.begin(); iter != m_openSet.end(); iter++)
        {
            if ((*iter)->getFscore() <= m_currentNode->getFscore())
            {
                m_currentNode = (*iter);
            }
        }

        if (m_currentNode == m_goalNode)
        {
            return reconstructPath(m_currentNode->getPreviousNode(), m_currentNode);
        }

        m_openSet.remove(m_currentNode);
        m_closedSet.push_back(m_currentNode);

        for each(Edge* currentEdge in *m_currentNode->getEdges())
        {
            PathNode* neighbor = (m_currentNode == currentEdge->m_firstNode ? currentEdge->m_secondNode : currentEdge->m_firstNode);

            // neighbor has not yet been processed
            if (std::find(m_closedSet.begin(), m_closedSet.end(), neighbor) == m_closedSet.end())
            {
                // if is not in the queue add it
                if (std::find(m_openSet.begin(), m_openSet.end(), neighbor) == m_openSet.end())
                {
                    m_openSet.push_back(neighbor);
                }

                float tentativeGscore = m_currentNode->getGscore() + magnitude(neighbor->getPosition() - m_currentNode->getPosition());
                if (tentativeGscore < neighbor->getGscore())
                {
                    neighbor->setPreviousNode(m_currentNode);
                    neighbor->setGscore(tentativeGscore);
                    neighbor->setFscore(neighbor->getGscore() + magnitude(m_goalNode->getPosition() - neighbor->getPosition()));
                }
            }
        }
    }

    std::list<PathNode*> a;
    return a;
}

std::list<PathNode*> PathFinder::reconstructPath(PathNode* cameFrom, PathNode* current)
{
    // backtrack to get the path
    std::list<PathNode*> totalPath;
    totalPath.push_back(current);
    while (std::find(m_closedSet.begin(), m_closedSet.end(), current) != m_closedSet.end())
    {
        current = current->getPreviousNode();
        totalPath.push_front(current);
    }

    return totalPath;
}