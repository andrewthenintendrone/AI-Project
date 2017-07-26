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

    // score access
    float getGscore();
    void setGscore(float newGscore);

    float getHscore();
    void setHscore(float newHscore);

    float getFscore();
    void setFscore(float newFscore);

    PathNode* getPreviousNode();
    void setPreviousNode(PathNode* newPreviousNode);

    std::list<Edge*>* getEdges();

private:
    // graphic
    sf::CircleShape m_graphic;

    // pathFinding
    std::list<Edge*> m_edges;

    float Gscore = std::numeric_limits<float>::infinity();
    float Hscore = std::numeric_limits<float>::infinity();
    float Fscore = std::numeric_limits<float>::infinity();
    PathNode* m_prevNode = nullptr;
};