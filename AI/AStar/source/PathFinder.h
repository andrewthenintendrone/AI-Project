#pragma once
#include "SFML\Graphics.hpp"
#include "PathNode.h"
#include <list>

enum class MOVESTATE { IDLE, WALK, RUN };
enum class MOVEDIRECTION { DOWN, LEFT, DOWNLEFT, UPLEFT, UP, RIGHT, DOWNRIGHT, UPRIGHT };

class PathFinder
{
public:
    PathFinder();
    ~PathFinder();

    void update();
    void draw();

    std::list<PathNode*> AStar(PathNode* start, PathNode* goal);

private:
    // graphics
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    MOVESTATE m_movementState = MOVESTATE::RUN;
    MOVEDIRECTION m_movementDirection = MOVEDIRECTION::DOWNRIGHT;
    sf::Vector2i currentSpriteCoordinate;
    int m_animationFrameRate = 10;
    sf::Clock m_clock;

    // Path Finding
    PathNode* m_startNode;
    PathNode* m_goalNode;
    PathNode* m_currentNode;

    std::list<PathNode*> m_openSet;
    std::list<PathNode*> m_closedSet;

    std::list<PathNode*> reconstructPath(PathNode* cameFrom, PathNode* current);
};