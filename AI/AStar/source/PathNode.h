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
    void removeSingleEdge(Edge* edgeToRemove);
    void deleteEdges();

    void draw();

    sf::CircleShape* getGraphic();
    sf::Vector2f getPosition();
    void setPosition(sf::Vector2f newPosition);

    void setColor(sf::Color newColor);

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

    void reset();

private:
    // graphic
    sf::CircleShape m_graphic;

    // list of attached edges
    std::list<Edge*> m_edges;

    // G, H, and F scores set to the default value of infinity
    float Gscore = std::numeric_limits<float>::infinity();
    float Hscore = std::numeric_limits<float>::infinity();
    float Fscore = std::numeric_limits<float>::infinity();

    // pointer to the previous node
    PathNode* m_prevNode = nullptr;
};