#include "PathFinder.h"
#include "Renderer.h"
#include "Edge.h"
#include "VectorMaths.h"
#include <algorithm>
#include "TimeManager.h"

std::string getPath();

const sf::Vector2i pathFinderSpriteSize(40, 56);

PathFinder::PathFinder()
{
    m_texture.loadFromFile(getPath() + "\\resources\\graphics\\sheet.png");
    m_sprite.setTexture(m_texture);

    m_sprite.setOrigin(sf::Vector2f(19, 46));
}

PathFinder::~PathFinder()
{

}

void PathFinder::update()
{
    if (m_followingPath == true)
    {
        followPath();
    }
    updateSprite();
}

void PathFinder::draw()
{
    Renderer::getInstance()->Draw(&m_sprite);
}

void PathFinder::seekToGoal(PathNode* start, PathNode* goal)
{
    m_startNode = start;
    m_goalNode = goal;

    m_bestPath.clear();
    m_bestPath = AStar();

    if (!m_bestPath.empty())
    {
        for (std::list<PathNode*>::iterator iter = m_bestPath.begin(); iter != std::prev(m_bestPath.end()); iter++)
        {
            for (std::list<Edge*>::iterator edgeiter = (*iter)->getEdges()->begin(); edgeiter != (*iter)->getEdges()->end(); edgeiter++)
            {
                if ((*edgeiter)->m_firstNode == (*iter) && (*edgeiter)->m_secondNode == *std::next(iter))
                {
                    (*edgeiter)->setColor(sf::Color(0, 0, 255));
                }
                else if ((*edgeiter)->m_secondNode == (*iter) && (*edgeiter)->m_firstNode == *std::next(iter))
                {
                    (*edgeiter)->setColor(sf::Color(0, 0, 255));
                }
            }
        }
        m_position = m_startNode->getPosition();
        m_currentTarget = (*std::next(m_bestPath.begin()));
        m_followingPath = true;
    }
}

void PathFinder::stopPathFinding()
{
    m_currentTarget = nullptr;
    m_velocity = sf::Vector2f(0, 0);
    m_followingPath = false;
}

// uses AStar to find the shortest path
std::list<PathNode*> PathFinder::AStar()
{
    m_closedSet.clear();
    m_openSet.clear();

    m_startNode->setGscore(0);
    m_startNode->setFscore(magnitude(m_goalNode->getPosition() - m_startNode->getPosition()));
    m_openSet.push_back(m_startNode);

    m_currentNode = m_startNode;

    while (!m_openSet.empty())
    {
        m_currentNode = m_openSet.front();

        for (std::list<PathNode*>::iterator iter = m_openSet.begin(); iter != m_openSet.end(); iter++)
        {
            if ((*iter)->getFscore() < m_currentNode->getFscore())
            {
                m_currentNode = (*iter);
            }
        }

        if (m_currentNode == m_goalNode)
        {
            return reconstructPath();
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

std::list<PathNode*> PathFinder::reconstructPath()
{
    PathNode* currentNode = m_goalNode;

    // backtrack to get the path
    std::list<PathNode*> totalPath;

    while (currentNode != m_startNode)
    {
        totalPath.push_front(currentNode);
        currentNode = currentNode->getPreviousNode();
    }
    totalPath.push_front(m_startNode);

    return totalPath;
}

void PathFinder::followPath()
{
    sf::Vector2f velocity = (m_currentTarget->getPosition() - m_position);

    if (distanceCheck(velocity, 1.0f))
    {
        m_velocity = normalize(velocity, 0.0f);
        if (m_currentTarget != m_bestPath.back())
        {
            m_currentTarget = *std::next(std::find(m_bestPath.begin(), m_bestPath.end(), m_currentTarget));
        }
        else
        {
            m_currentTarget = *std::next(m_bestPath.begin());
            m_position = m_bestPath.front()->getPosition();
        }
    }
    else if (m_currentTarget == m_bestPath.back() && distanceCheck(velocity, m_slowRadius))
    {
        m_velocity = normalize(velocity, magnitude(velocity) / m_slowRadius * m_maxVelocity * TIMEMANAGER->deltaTime());
    }
    else
    {
        m_velocity = normalize(velocity, m_maxVelocity * TIMEMANAGER->deltaTime());
    }

    m_position += m_velocity;
    m_sprite.setPosition(m_position);
}

void PathFinder::updateSprite()
{
    if (distanceCheck(m_velocity / TIMEMANAGER->deltaTime(), 0.0f))
    {
        m_movementState = MOVESTATE::IDLE;
    }
    else
    {
        if (distanceCheck(m_velocity / TIMEMANAGER->deltaTime(), m_slowRadius))
        {
            m_movementState = MOVESTATE::WALK;
        }
        else
        {
            m_movementState = MOVESTATE::RUN;
        }

        float movementAngle = vectorAngle(m_velocity);

        if (movementAngle <= 22.5f || movementAngle > 337.5f)
        {
            m_movementDirection = MOVEDIRECTION::RIGHT;
        }
        else if (movementAngle <= 67.5f)
        {
            m_movementDirection = MOVEDIRECTION::DOWNRIGHT;
        }
        else if (movementAngle <= 112.5f)
        {
            m_movementDirection = MOVEDIRECTION::DOWN;
        }
        else if (movementAngle <= 157.5f)
        {
            m_movementDirection = MOVEDIRECTION::DOWNLEFT;
        }
        else if (movementAngle <= 202.5f)
        {
            m_movementDirection = MOVEDIRECTION::LEFT;
        }
        else if (movementAngle <= 247.5f)
        {
            m_movementDirection = MOVEDIRECTION::UPLEFT;
        }
        else if (movementAngle <= 292.5f)
        {
            m_movementDirection = MOVEDIRECTION::UP;
        }
        else if (movementAngle <= 337.5f)
        {
            m_movementDirection = MOVEDIRECTION::UPRIGHT;
        }
    }

    // animation
    if (m_clock.getElapsedTime().asSeconds() > (1.0f / (float)m_animationFrameRate))
    {
        currentSpriteCoordinate.x += pathFinderSpriteSize.x;
        if (currentSpriteCoordinate.x == (pathFinderSpriteSize.x * 6))
        {
            currentSpriteCoordinate.x = 0;
        }
        m_clock.restart();
    }

    // move to part of the sprite sheet based on movement state
    currentSpriteCoordinate.y = (int)m_movementState * (pathFinderSpriteSize.y * 5);
    currentSpriteCoordinate.y += ((int)m_movementDirection > 4 ? (int)m_movementDirection - 4 : (int)m_movementDirection) * pathFinderSpriteSize.y;

    if ((int)m_movementDirection < 5)
    {
        m_sprite.setScale(1, 1);
    }
    else
    {
        m_sprite.setScale(-1, 1);
    }
    m_sprite.setTextureRect(sf::IntRect(currentSpriteCoordinate, pathFinderSpriteSize));
}