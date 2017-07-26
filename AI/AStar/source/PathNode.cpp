#include "PathNode.h"
#include "Renderer.h"
#include "Edge.h"

PathNode::PathNode(sf::Vector2f newPosition)
{
    // node graphic
    m_graphic.setRadius(10.0f);
    m_graphic.setOutlineThickness(5.0f);

    m_graphic.setFillColor(sf::Color::Blue);
    m_graphic.setOutlineColor(sf::Color::Black);

    m_graphic.setOrigin(m_graphic.getLocalBounds().width / 2 - m_graphic.getOutlineThickness(), m_graphic.getGlobalBounds().height / 2 - m_graphic.getOutlineThickness());
    m_graphic.setPosition(newPosition);
}

PathNode::~PathNode()
{
    // TO DO
    // removes itself from all neighbors
    /*for (std::list<Edge2*>::iterator iter = m_edges.begin(); iter != m_edges.end();)
    {

    }*/
}

void PathNode::addEdge(Edge* newEdge)
{
    m_edges.push_back(newEdge);
}

void PathNode::removeEdge(Edge* edgeToRemove)
{
    m_edges.remove(edgeToRemove);
}

void PathNode::draw()
{
    Renderer::getInstance()->Draw(&m_graphic);
    for (std::list<Edge*>::iterator iter = m_edges.begin(); iter != m_edges.end(); iter++)
    {
        (*iter)->draw();
    }
}

sf::CircleShape * PathNode::getGraphic()
{
    return &m_graphic;
}

sf::Vector2f PathNode::getPosition()
{
    return m_graphic.getPosition();
}

float PathNode::getGscore()
{
    return Gscore;
}

void PathNode::setGscore(float newGscore)
{
    Gscore = newGscore;
}

float PathNode::getHscore()
{
    return Hscore;
}

void PathNode::setHscore(float newHscore)
{
    Hscore = newHscore;
}

float PathNode::getFscore()
{
    return Fscore;
}

void PathNode::setFscore(float newFscore)
{
    Fscore = newFscore;
}
