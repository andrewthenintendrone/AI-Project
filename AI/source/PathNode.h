#pragma once
#include "SFML\Graphics.hpp"
#include <list>
#include "Edge.h"

const sf::Color fillColor = sf::Color(79, 129, 189);
const sf::Color outlineColor = sf::Color(56, 93, 138);

class PathNode
{
public:
    PathNode(sf::Vector2f newPosition, sf::Font* newFont, unsigned int newNumber);
    void draw();

    sf::Vector2f getPosition();
private:
    std::list<Edge*> edges;
    float Gscore;
    float Hscore;
    float Fscore;
    sf::Vector2f position;
    sf::CircleShape nodeGraphic;
    sf::Text nodeText;

    void setUp();
};