#include "Renderer.h"
#include "PathNode.h"

PathNode::PathNode(sf::Vector2f newPosition, sf::Font* newFont, unsigned int newNumber)
{
    position = newPosition;
    nodeText.setFont(*newFont);
    nodeText.setString(std::to_string(newNumber));
    setUp();
}

void PathNode::draw()
{
    Renderer::getInstance()->Draw(&nodeGraphic);
    Renderer::getInstance()->Draw(&nodeText);
    for each (Edge* currentEdge in edges)
    {
        currentEdge->draw();
    }
}

sf::Vector2f PathNode::getPosition()
{
    return position;
}

void PathNode::setUp()
{
    // node graphic
    nodeGraphic.setRadius(35.0f);
    nodeGraphic.setOutlineThickness(5.0f);

    nodeGraphic.setFillColor(fillColor);
    nodeGraphic.setOutlineColor(outlineColor);

    nodeGraphic.setOrigin(nodeGraphic.getLocalBounds().width / 2, nodeGraphic.getLocalBounds().height / 2);
    nodeGraphic.setPosition(position);

    // text
    nodeText.setCharacterSize(32);
    nodeText.setFillColor(sf::Color::White);
    nodeText.setOrigin(nodeText.getLocalBounds().width, nodeText.getLocalBounds().height);
    nodeText.setPosition(position);
}