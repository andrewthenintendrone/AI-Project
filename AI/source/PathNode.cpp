#include "Renderer.h"
#include "PathNode.h"
#include "GlobalFont.h"

PathNode::PathNode(sf::Vector2f newPosition, unsigned int newNumber)
{
    position = newPosition;
    nodeText.setFont(GlobalFont::getInstance());
    nodeText.setString(std::to_string(newNumber));
    setUp();
}

void PathNode::addEdge(std::shared_ptr<Edge> newEdge)
{
    edges.push_back(newEdge);
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

void PathNode::setUp()
{
    // node graphic
    nodeGraphic.setRadius(35.0f);
    nodeGraphic.setOutlineThickness(5.0f);

    nodeGraphic.setFillColor(fillColor);
    nodeGraphic.setOutlineColor(outlineColor);

    nodeGraphic.setOrigin(nodeGraphic.getLocalBounds().width / 2 - 2.5f, nodeGraphic.getLocalBounds().height / 2 - 2.5f);
    nodeGraphic.setPosition(position);

    // text
    nodeText.setCharacterSize(32);
    nodeText.setFillColor(sf::Color::White);
    nodeText.setOrigin(nodeText.getLocalBounds().width, nodeText.getLocalBounds().height);
    nodeText.setPosition(position);
}