#pragma once
#include "SFML\Graphics.hpp"
#include <vector>
#include "Edge.h"
#include <memory>

const sf::Color fillColor = sf::Color(79, 129, 189);
const sf::Color fillColorSelected = sf::Color(128, 100, 162);
const sf::Color outlineColor = sf::Color(56, 93, 138);
const sf::Color outlineColorSelected = sf::Color(92, 71, 118);

class PathNode
{
public:
    PathNode(sf::Vector2f newPosition, sf::Font& newFont, unsigned int newNumber);
    void addEdge(std::shared_ptr<Edge> newEdge);
    void update();
    void dragWithMouse(sf::Vector2f mousePos);
    void draw();

    bool selected = false;

    sf::Vector2f getPosition();
    sf::FloatRect getBounds();
private:
    std::vector<std::shared_ptr<Edge>> edges;
    float Gscore;
    float Hscore;
    float Fscore;
    sf::Vector2f position;
    sf::CircleShape nodeGraphic;
    sf::Text nodeText;

    void setUp();
};