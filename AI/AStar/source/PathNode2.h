#pragma once
#include "SFML\Graphics.hpp"
#include <list>
#include <limits>

class Edge2;

class PathNode2
{
public:
    PathNode2(sf::Vector2f newPosition);
    ~PathNode2();


    void addEdge(Edge2* newEdge);
    void removeEdge(Edge2* edgeToRemove);

    void draw();

    sf::CircleShape* getGraphic();
    sf::Vector2f getPosition();

private:
    sf::CircleShape m_graphic;

    std::list<Edge2*> m_edges;
};