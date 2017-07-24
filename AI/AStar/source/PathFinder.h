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

    std::list<PathNode*> findShortestPath();

private:
    // graphic
    sf::Texture* m_texture;
    sf::Sprite* m_sprite;

    // Path Finding
    Path* m_path;

    PathNode* currentNode;
    PathNode* goalNode;
    std::list<PathNode*> openSet;
    std::list<PathNode*> closedSet;

    std::list<PathNode*> reconstructPath(PathNode* cameFrom, PathNode* current);
};