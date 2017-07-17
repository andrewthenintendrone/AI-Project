#include "Edge.h"
#include "PathNode.h"
#include "Renderer.h"
#include "VectorMaths.h"

std::string getPath();

Edge::Edge(PathNode* newFirstNode, PathNode* newSecondNode)
{
    firstNode = newFirstNode;
    secondNode = newSecondNode;
    m_font.loadFromFile(getPath() + "\\resources\\font\\calibri.ttf");
    distanceText.setFont(m_font);
    distanceText.setCharacterSize(40);
    distanceText.setFillColor(sf::Color::White);

    recalculate();
}

Edge::~Edge()
{
    firstNode->getEdges().remove(this);
    secondNode->getEdges().remove(this);
}

void Edge::draw()
{
    Renderer::getInstance()->getWindow().draw(graphic);
    Renderer::getInstance()->getWindow().draw(distanceText);
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

    distanceText.setString(std::to_string((int)lineLength));
    distanceText.setOrigin(distanceText.getLocalBounds().width / 2, distanceText.getLocalBounds().height);
    distanceText.setPosition(centerOfNodes);
}