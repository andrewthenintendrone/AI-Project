#pragma once
#include "SFML\Graphics.hpp"
#include "PathNode.h"
#include <list>

class PathFinder
{
public:
    PathFinder(PathNode* start, PathNode* goal);
    ~PathFinder();

    void Update();

    std::list<PathNode*> AStar();

private:
    // graphics
    sf::Texture* m_texture;
    sf::Sprite* m_sprite;

    // Path Finding
    PathNode* m_startNode;
    PathNode* m_goalNode;

    std::list<PathNode*> m_openSet;
    std::list<PathNode*> m_closedSet;

    std::list<PathNode*> reconstructPath(PathNode* cameFrom, PathNode* current);
};