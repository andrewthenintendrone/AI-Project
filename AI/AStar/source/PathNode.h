#pragma once
#include "SFML\Graphics.hpp"
#include <list>
#include "Edge.h"
#include <limits>

const sf::Color fillColor = sf::Color(79, 129, 189);
const sf::Color fillColorSelected = sf::Color(128, 100, 162);
const sf::Color outlineColor = sf::Color(56, 93, 138);
const sf::Color outlineColorSelected = sf::Color(92, 71, 118);

enum class NodeType { STARTNODE, NODE, ENDNODE, ONLYNODE };

class PathNode
{
public:
    PathNode(sf::Vector2f newPosition, unsigned int newNumber);
    ~PathNode();
    void addEdge(Edge* newEdge);
    void update(bool selected);
    void dragWithMouse(sf::Vector2f mousePos);
    void draw();

    void setNodeType(NodeType newNodeType);
    void setPrevNode(PathNode* newPrevNode);
    PathNode* getPrevNode();
    void setGScore(float newGScore);
    float getGScore();


    sf::Vector2f getPosition();
    sf::FloatRect getBounds();
    std::list<Edge*>* getEdges();
private:
    std::list<Edge*> edges;
    sf::Vector2f position;
    sf::CircleShape nodeGraphic;
    sf::Font m_font;
    sf::Text nodeText;


    NodeType m_nodeType = NodeType::NODE;
    float Gscore = std::numeric_limits<float>::infinity();
    //float Hscore;
    //float Fscore;

    PathNode* m_prevNode = nullptr;

    void setUp();
};