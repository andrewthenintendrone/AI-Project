#include "Renderer.h"
#include "PathNode.h"

PathNode::PathNode(sf::Vector2f newPosition, sf::Font& newFont, unsigned int newNumber)
{
    position = newPosition;
    nodeText.setFont(newFont);
    nodeText.setString(std::to_string(newNumber));
    setUp();
}

void PathNode::addEdge(std::shared_ptr<Edge> newEdge)
{
    edges.push_back(newEdge);
}

void PathNode::update()
{
    nodeGraphic.setFillColor(fillColor);
    nodeGraphic.setOutlineColor(outlineColor);
    if (selected)
    {
        dragWithMouse(sf::Vector2f(sf::Mouse::getPosition(Renderer::getInstance()->getWindow())));
    }
}

void PathNode::dragWithMouse(sf::Vector2f mousePos)
{
    nodeGraphic.setFillColor(fillColorSelected);
    nodeGraphic.setOutlineColor(outlineColorSelected);
    position = mousePos;
    nodeGraphic.setPosition(position);
    nodeText.setPosition(position);
    for (std::vector<std::shared_ptr<Edge>>::iterator iter = edges.begin(); iter != edges.end(); iter++)
    {
        iter->get()->recalculate();
    }
}

void PathNode::draw()
{
    Renderer::getInstance()->Draw(&nodeGraphic);
    Renderer::getInstance()->Draw(&nodeText);
    for (std::vector<std::shared_ptr<Edge>>::iterator iter = edges.begin(); iter != edges.end(); iter++)
    {
        iter->get()->draw();
    }
}

sf::Vector2f PathNode::getPosition()
{
    return position;
}

sf::FloatRect PathNode::getBounds()
{
    return nodeGraphic.getGlobalBounds();
}

void PathNode::setUp()
{
    // node graphic
    nodeGraphic.setRadius(35.0f);
    nodeGraphic.setOutlineThickness(5.0f);

    nodeGraphic.setFillColor(fillColor);
    nodeGraphic.setOutlineColor(outlineColor);

    nodeGraphic.setOrigin(nodeGraphic.getLocalBounds().width / 2 - nodeGraphic.getOutlineThickness(), nodeGraphic.getGlobalBounds().height / 2 - nodeGraphic.getOutlineThickness());
    nodeGraphic.setPosition(position);

    // text
    nodeText.setCharacterSize(40);
    nodeText.setFillColor(sf::Color::White);
    nodeText.setOrigin(nodeText.getLocalBounds().width / 2, nodeText.getLocalBounds().height);
    nodeText.setPosition(position);
}