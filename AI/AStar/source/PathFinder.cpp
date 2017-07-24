#include "PathFinder.h"
#include "Renderer.h"
#include "Path.h"

std::string getPath();

PathFinder::PathFinder(Path* newPath)
{
    m_path = newPath;

    m_texture = new sf::Texture;
    m_texture->loadFromFile(getPath() + "\\resources\\graphics\\PathFinder.png");
    m_sprite = new sf::Sprite;
    m_sprite->setTexture(*m_texture);

    m_sprite->setOrigin(sf::Vector2f(m_sprite->getGlobalBounds().width / 2.0f, m_sprite->getGlobalBounds().height / 2.0f));
    m_sprite->setPosition(m_path->getNode(0)->getPosition());
}

PathFinder::~PathFinder()
{
    delete m_sprite;
    delete m_texture;
}

void PathFinder::Update()
{
    Renderer::getInstance()->Draw(m_sprite);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        std::list<PathNode*> shortestPath = findShortestPath();
        int x = 0;
    }
}

// uses AStar to find the shortest path
std::list<PathNode*> PathFinder::findShortestPath()
{
    goalNode = m_path->getLastNode();

    currentNode = m_path->getNode(0);
    currentNode->setPrevNode(currentNode);
    currentNode->setGScore(0);

    // Push start node onto priority queue
    openSet.push_back(currentNode);

    // while queue is not empty
    while (!openSet.empty())
    {
        // find next node by priority
        for (auto iter = openSet.begin(); iter != openSet.end(); iter++)
        {
            if ((*iter)->getGScore() < currentNode->getGScore())
            {
                currentNode = (*iter);
            }
        }

        if (currentNode == goalNode)
        {
            return reconstructPath(currentNode->getPrevNode(), currentNode);
        }

        // mark that node as traversed
        openSet.remove(currentNode);
        closedSet.push_back(currentNode);

        // loop through the current node's edges
        for each(Edge* currentEdge in *currentNode->getEdges())
        {
            PathNode* endNode;

            // find which node
            //endNode = (currentNode == currentEdge->firstNode) ? currentEdge->secondNode : currentEdge->firstNode;

            endNode = currentEdge->secondNode;

            // next node has already been processed
            if (std::find(closedSet.begin(), closedSet.end(), endNode) != closedSet.end())
            {
                continue;
            }
            // has not been processed
            // add it to the priority queue
            else
            {
                openSet.push_back(endNode);
            }

            float newGScore = currentNode->getGScore() + currentEdge->length();

            if (newGScore >= endNode->getGScore())
            {
                continue;
            }

            endNode->setPrevNode(currentNode);
            endNode->setGScore(newGScore);
        }
    }
}

std::list<PathNode*> PathFinder::reconstructPath(PathNode* cameFrom, PathNode* current)
{
    // backtrack to get the path
    std::list<PathNode*> totalPath;
    totalPath.push_back(current);
    while (std::find(closedSet.begin(), closedSet.end(), current) != closedSet.end())
    {
        current = current->getPrevNode();
        totalPath.push_front(current);
    }

    return totalPath;
}