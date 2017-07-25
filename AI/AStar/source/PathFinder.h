#pragma once
#include "SFML\Graphics.hpp"
#include "PathNode.h"
#include <list>

class Path;

class PathFinder
{
public:
    PathFinder(Path* newPath);
    ~PathFinder();

    void Update();

    std::list<PathNode*> AStar();

private:
    // graphic
    sf::Texture* m_texture;
    sf::Sprite* m_sprite;

    // Path Finding
    Path* m_path;

    PathNode* m_currentNode;
    PathNode* m_goalNode;
    std::list<PathNode*> m_openSet;
    std::list<PathNode*> m_closedSet;

    std::list<PathNode*> reconstructPath(PathNode* cameFrom, PathNode* current);
};