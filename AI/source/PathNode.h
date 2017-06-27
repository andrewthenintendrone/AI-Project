#pragma once
#include "SFML\Graphics.hpp"
#include <vector>
#include "Edge.h"
#include <memory>

const sf::Color fillColor = sf::Color(79, 129, 189);
const sf::Color outlineColor = sf::Color(56, 93, 138);

class PathNode
{
public:
    PathNode(sf::Vector2f newPosition, unsigned int newNumber);
    void addEdge(std::shared_ptr<Edge> newEdge);
    void draw();

    sf::Vector2f getPosition();
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