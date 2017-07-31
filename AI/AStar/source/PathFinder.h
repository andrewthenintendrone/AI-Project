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

    void seekToGoal(PathNode* start, PathNode* goal);
    void stopPathFinding();

    std::list<PathNode*> m_bestPath;
private:
    // graphics
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    MOVESTATE m_movementState = MOVESTATE::RUN;
    MOVEDIRECTION m_movementDirection = MOVEDIRECTION::DOWNRIGHT;
    sf::Vector2i currentSpriteCoordinate;
    int m_animationFrameRate = 10;
    sf::Clock m_clock;
    void updateSprite();

    // Path Finding
    PathNode* m_startNode = nullptr;
    PathNode* m_goalNode = nullptr;
    PathNode* m_currentNode = nullptr;

    std::list<PathNode*> m_openSet;
    std::list<PathNode*> m_closedSet;

    std::list<PathNode*> AStar();
    std::list<PathNode*> reconstructPath();

    // movement
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;

    float m_maxVelocity = 300.0f;
    float m_slowRadius = 100.0f;

    PathNode* m_currentTarget;
    bool m_followingPath = false;
    void followPath();
};