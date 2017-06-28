#include "Edge.h"
#include "PathNode.h"
#include "Renderer.h"
#include "VectorMaths.h"

Edge::Edge(std::shared_ptr<PathNode>newFirstNode, std::shared_ptr<PathNode>newSecondNode)
{
    firstNode = newFirstNode;
    secondNode = newSecondNode;
    recalculate();
}

void Edge::draw()
{
    Renderer::getInstance()->getWindow().draw(graphic);
}

void Edge::recalculate()
{
    sf::Vector2f centerOfNodes = (firstNode->getPosition() + secondNode->getPosition()) / 2.0f;
    float rotationAngle = angleBetweenVectors(firstNode->getPosition(), secondNode->getPosition());
    float lineLength = magnitude(secondNode->getPosition() - firstNode->getPosition()) - 80.0f;

    graphic.setSize(sf::Vector2f(lineLength, 3));
    graphic.setOrigin(graphic.getLocalBounds().width / 2, graphic.getLocalBounds().height / 2);
    graphic.setPosition(centerOfNodes);
    graphic.setRotation(rotationAngle);
    graphic.setFillColor(edgeColor);
}