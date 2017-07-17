#pragma once
#include "SFML\Graphics.hpp"
#include <list>
#include "Edge.h"

const sf::Color fillColor = sf::Color(79, 129, 189);
const sf::Color fillColorSelected = sf::Color(128, 100, 162);
const sf::Color outlineColor = sf::Color(56, 93, 138);
const sf::Color outlineColorSelected = sf::Color(92, 71, 118);

class PathNode
{
public:
    PathNode(sf::Vector2f newPosition, sf::Font& newFont, unsigned int newNumber);
    void addEdge(Edge* newEdge);
    void remove();
    void update(bool selected);
    void dragWithMouse(sf::Vector2f mousePos);
    void draw();

    sf::Vector2f getPosition();
    sf::FloatRect getBounds();
    std::list<Edge*>& getEdges();
private:
    std::list<Edge*> edges;
    float Gscore;
    float Hscore;
    float Fscore;
    sf::Vector2f position;
    sf::CircleShape nodeGraphic;
    sf::Font m_font;
    sf::Text nodeText;

    void setUp();
};