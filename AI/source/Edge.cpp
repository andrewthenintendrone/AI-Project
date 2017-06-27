#include "Edge.h"
#include "PathNode.h"
#include "Renderer.h"
#include "VectorMaths.h"

void Edge::draw()
{
    sf::Vector2f centerOfNodes = (firstNode->getPosition() + secondNode->getPosition()) / 2.0f;
    float rotationAngle = angleBetweenVectors(secondNode->getPosition(), firstNode->getPosition());
    float lineLength = magnitude(firstNode->getPosition() - secondNode->getPosition());

    sf::RectangleShape line(sf::Vector2f(lineLength, 5));
    line.setRotation(rotationAngle);
    line.setOrigin(line.getLocalBounds().width / 2, line.getLocalBounds().height / 2);
    line.setPosition(centerOfNodes);
    line.setFillColor(edgeColor);

    Renderer::getInstance()->getWindow().draw(line);
}