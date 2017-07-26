#pragma once
#include "SFML\Graphics.hpp"
#include <list>
#include <limits>

class Edge;

class PathNode
{
public:
    PathNode(sf::Vector2f newPosition);
    ~PathNode();


    void addEdge(Edge* newEdge);
    void removeEdge(Edge* edgeToRemove);

    void draw();

    sf::CircleShape* getGraphic();
    sf::Vector2f getPosition();

private:
    // graphic
    sf::CircleShape m_graphic;

    // pathFinding
    std::list<Edge*> m_edges;

    float FScore = std::numeric_limits<float>::infinity();
    float GScore = std::numeric_limits<float>::infinity();
    float Hscore = std::numeric_limits<float>::infinity();
};