#pragma once
class PathNode;
#include "SFML\Graphics.hpp"
#include <memory>

const sf::Color edgeColor = sf::Color(192, 80, 77);

class Edge
{
public:
    Edge(std::shared_ptr<PathNode> newFirstNode, std::shared_ptr<PathNode> newSecondNode);
    std::shared_ptr<PathNode> firstNode;
    std::shared_ptr<PathNode> secondNode;

    void recalculate();
    void draw();

private:
    sf::RectangleShape graphic;
};