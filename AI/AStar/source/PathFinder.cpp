#include "PathFinder.h"
#include "Renderer.h"
#include "Edge.h"
#include "VectorMaths.h"
#include <algorithm>
#include "TimeManager.h"

std::string getPath();

// sprite size is a constant
const sf::Vector2i pathFinderSpriteSize(40, 56);

// constructor loads the sprite sheet and sets the origin to the feet
PathFinder::PathFinder()
{
    m_texture.loadFromFile(getPath() + "\\resources\\graphics\\Character.png");
    m_sprite.setTexture(m_texture);

    m_sprite.setOrigin(sf::Vector2f(19, 46));
}

// destructor
PathFinder::~PathFinder()
{

}

// update function
void PathFinder::update()
{
    // follow path if applicable
    if (m_followingPath == true)
    {
        followPath();
    }

    // update sprite
    updateSprite();
}

// draw function
void PathFinder::draw()
{
    // draw the sprite
    Renderer::getInstance()->Draw(&m_sprite);
}

// calculates the best path from the start node to the end node then travels along it
void PathFinder::seekToGoal(PathNode* start, PathNode* goal)
{
    // store the start and end node
    m_startNode = start;
    m_goalNode = goal;

    // recalculate the best path
    m_bestPath.clear();
    m_bestPath = AStar();

    // if there is a valid path
    if (!m_bestPath.empty())
    {
        for (std::list<PathNode*>::iterator iter = m_bestPath.begin(); iter != std::prev(m_bestPath.end()); iter++)
        {
            for (std::list<Edge*>::iterator edgeiter = (*iter)->getEdges()->begin(); edgeiter != (*iter)->getEdges()->end(); edgeiter++)
            {
                // color its edges blue to stand out from the other edges
                if ((*edgeiter)->m_firstNode == (*iter) && (*edgeiter)->m_secondNode == *std::next(iter))
                {
                    (*edgeiter)->setColor(Edge::BLUE());
                }
                else if ((*edgeiter)->m_secondNode == (*iter) && (*edgeiter)->m_firstNode == *std::next(iter))
                {
                    (*edgeiter)->setColor(Edge::BLUE());
                }
            }
        }

        // set position to the start node
        m_position = m_startNode->getPosition();

        // set the current target node to the second node of the path
        m_currentTarget = (*std::next(m_bestPath.begin()));

        // pathfinder is now ready to traverse the path
        m_followingPath = true;
    }
}

// stop following the path
void PathFinder::stopPathFinding()
{
    m_currentTarget = nullptr;
    m_velocity = sf::Vector2f(0, 0);
    m_followingPath = false;
}

// uses AStar to return the shortest path
std::list<PathNode*> PathFinder::AStar()
{
    // clear both sets
    m_closedSet.clear();
    m_openSet.clear();

    // set the start nodes Gscore to 0 and calculate its Fscore using only the heuristic
    m_startNode->setGscore(0);
    m_startNode->setFscore(magnitude(m_goalNode->getPosition() - m_startNode->getPosition()));

    // push the start node onto the open set
    m_openSet.push_back(m_startNode);

    // set the currentNode to the start node we just pushed back
    m_currentNode = m_startNode;

    while (!m_openSet.empty())
    {
        // choose the node with the highest priority from the open set
        m_currentNode = m_openSet.front();

        for (std::list<PathNode*>::iterator iter = m_openSet.begin(); iter != m_openSet.end(); iter++)
        {
            if ((*iter)->getFscore() < m_currentNode->getFscore())
            {
                m_currentNode = (*iter);
            }
        }

        // if we have reached the goal reconstruct the path and return it
        if (m_currentNode == m_goalNode)
        {
            return reconstructPath();
        }

        // mark the current node as looked at
        m_openSet.remove(m_currentNode);
        m_closedSet.push_back(m_currentNode);

        for each(Edge* currentEdge in *m_currentNode->getEdges())
        {
            // get a neighboring path node from the current node
            PathNode* neighbor = (m_currentNode == currentEdge->m_firstNode ? currentEdge->m_secondNode : currentEdge->m_firstNode);

            // neighbor has not yet been processed
            if (std::find(m_closedSet.begin(), m_closedSet.end(), neighbor) == m_closedSet.end())
            {
                // if is not in the queue add it
                if (std::find(m_openSet.begin(), m_openSet.end(), neighbor) == m_openSet.end())
                {
                    m_openSet.push_back(neighbor);
                }

                // calculate a tentative Gscore
                float tentativeGscore = m_currentNode->getGscore() + currentEdge->m_length;

                // if the new Gscore is lower replace it and recalculate the other scores
                if (tentativeGscore < neighbor->getGscore())
                {
                    neighbor->setPreviousNode(m_currentNode);
                    neighbor->setGscore(tentativeGscore);
                    neighbor->setFscore(neighbor->getGscore() + magnitude(m_goalNode->getPosition() - neighbor->getPosition()));
                }
            }
        }
    }

    // if a path was not found between the start and end nodes return an empty list
    std::list<PathNode*> emptyList;
    return emptyList;
}

// trace backwards from the goal node to create a list of only the best nodes
std::list<PathNode*> PathFinder::reconstructPath()
{
    // create a list called totalPath to hold the final path
    std::list<PathNode*> totalPath;

    // while the currentNode is not the start node
    while (m_currentNode != m_startNode)
    {
        totalPath.push_front(m_currentNode);
        m_currentNode = m_currentNode->getPreviousNode();
    }

    // finally add the start node to the path
    totalPath.push_front(m_startNode);

    // return the finished path
    return totalPath;
}

// move along the path
void PathFinder::followPath()
{
    sf::Vector2f velocity = (m_currentTarget->getPosition() - m_position);
    
    // if we have reached our target
    if (distanceCheck(velocity, 1.0f))
    {
        // stop moving
        m_velocity = normalize(velocity, 0.0f);

        // target the next node in the path
        if (m_currentTarget != m_bestPath.back())
        {
            m_currentTarget = *std::next(std::find(m_bestPath.begin(), m_bestPath.end(), m_currentTarget));
        }
        // if we have reached the end of the path
        else
        {
            //set our target to the second node
            m_currentTarget = *std::next(m_bestPath.begin());

            // set our position to the first node
            m_position = m_bestPath.front()->getPosition();
        }
    }
    // only slow down for the goal node
    else if (m_currentTarget == m_bestPath.back() && distanceCheck(velocity, m_slowRadius))
    {
        m_velocity = normalize(velocity, magnitude(velocity) / m_slowRadius * m_maxVelocity * TIMEMANAGER->deltaTime());
    }
    // otherwise move at full speed
    else
    {
        m_velocity = normalize(velocity, m_maxVelocity * TIMEMANAGER->deltaTime());
    }

    // add the velocity to our position and update the sprite to that position
    m_position += m_velocity;
    m_sprite.setPosition(m_position);
}

// display different frames from the spritesheet based on the movement state and direction
void PathFinder::updateSprite()
{
    // if our velocity is zero we are not moving so set our movement state to IDLE
    if (distanceCheck(m_velocity / TIMEMANAGER->deltaTime(), 0.0f))
    {
        m_movementState = MOVESTATE::IDLE;
    }
    // otherwise we are moving
    else
    {
        // if our movement speed is lower than our slowdown radius then we are walking so set our movement state to WALK
        if (distanceCheck(m_velocity / TIMEMANAGER->deltaTime(), m_slowRadius))
        {
            m_movementState = MOVESTATE::WALK;
        }
        // otherwise we are running
        else
        {
            m_movementState = MOVESTATE::RUN;
        }

        // calculate the angle in degrees that our velocity is taking us
        float movementAngle = vectorAngle(m_velocity);

        // set our movement direction based on which 45 degree increment we are within
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

    // only change the current animation frame every 1 / framerate seconds
    if (m_clock.getElapsedTime().asSeconds() > (1.0f / (float)m_animationFrameRate))
    {
        // move along the spritesheet by the width of one cell
        currentSpriteCoordinate.x += pathFinderSpriteSize.x;

        // if we have left the coordinates of the spritesheet set x back to zero
        if (currentSpriteCoordinate.x == (pathFinderSpriteSize.x * 6))
        {
            currentSpriteCoordinate.x = 0;
        }

        // restart the clock to wait fo the next frame change
        m_clock.restart();
    }

    // move to part of the sprite sheet based on movement state
    currentSpriteCoordinate.y = static_cast<int>(m_movementState) * (pathFinderSpriteSize.y * 5);
    currentSpriteCoordinate.y += (static_cast<int>(m_movementDirection) > 4 ? static_cast<int>(m_movementDirection) - 4 : static_cast<int>(m_movementDirection)) * pathFinderSpriteSize.y;

    // for movement directions less than 5 display the sprite as normal
    if (static_cast<int>(m_movementDirection) < 5)
    {
        m_sprite.setScale(1, 1);
    }
    // the other movent directions just mirror the sprite
    else
    {
        m_sprite.setScale(-1, 1);
    }

    // set the displayed area of the sprite sheet
    m_sprite.setTextureRect(sf::IntRect(currentSpriteCoordinate, pathFinderSpriteSize));
}