#include "Renderer.h"
#include "PathNode.h"

std::string getPath();

PathNode::PathNode(sf::Vector2f newPosition, unsigned int newNumber)
{
    position = newPosition;
    m_font.loadFromFile(getPath() + "\\resources\\font\\calibri.ttf");
    nodeText.setFont(m_font);
    nodeText.setString(std::to_string(newNumber));
    setUp();
}

PathNode::~PathNode()
{
    while (!edges.empty())
    {
        delete edges.back();
    }
}

void PathNode::addEdge(Edge* newEdge)
{
    edges.push_back(newEdge);
}

void PathNode::update(bool selected)
{
    if (selected)
    {
        nodeGraphic.setFillColor(fillColorSelected);
        nodeGraphic.setOutlineColor(outlineColorSelected);
    }
    else
    {
        nodeGraphic.setFillColor(fillColor);
        nodeGraphic.setOutlineColor(outlineColor);
    }
}

void PathNode::dragWithMouse(sf::Vector2f mousePos)
{
    position = mousePos;
    nodeGraphic.setPosition(position);
    nodeText.setPosition(position);
    for (std::list<Edge*>::iterator iter = edges.begin(); iter != edges.end(); iter++)
    {
        (*iter)->recalculate();
    }
}

void PathNode::draw()
{
    Renderer::getInstance()->Draw(&nodeGraphic);
    Renderer::getInstance()->Draw(&nodeText);
    for (auto iter = edges.begin(); iter != edges.end(); iter++)
    {
        (*iter)->draw();
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

std::list<Edge*>* PathNode::getEdges()
{
    return &edges;
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