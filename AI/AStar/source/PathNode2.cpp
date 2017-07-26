#include "PathNode2.h"
#include "Renderer.h"
#include "Edge2.h"

PathNode2::PathNode2(sf::Vector2f newPosition)
{
    // node graphic
    m_graphic.setRadius(10.0f);
    m_graphic.setOutlineThickness(5.0f);

    m_graphic.setFillColor(sf::Color::Blue);
    m_graphic.setOutlineColor(sf::Color::Black);

    m_graphic.setOrigin(m_graphic.getLocalBounds().width / 2 - m_graphic.getOutlineThickness(), m_graphic.getGlobalBounds().height / 2 - m_graphic.getOutlineThickness());
    m_graphic.setPosition(newPosition);
}

PathNode2::~PathNode2()
{
    // TO DO
    // removes itself from all neighbors
    /*for (std::list<Edge2*>::iterator iter = m_edges.begin(); iter != m_edges.end();)
    {

    }*/
}

void PathNode2::addEdge(Edge2* newEdge)
{
    m_edges.push_back(newEdge);
}

void PathNode2::removeEdge(Edge2* edgeToRemove)
{
    m_edges.remove(edgeToRemove);
}

void PathNode2::draw()
{
    Renderer::getInstance()->Draw(&m_graphic);
    for (std::list<Edge2*>::iterator iter = m_edges.begin(); iter != m_edges.end(); iter++)
    {
        (*iter)->draw();
    }
}

sf::CircleShape * PathNode2::getGraphic()
{
    return &m_graphic;
}

sf::Vector2f PathNode2::getPosition()
{
    return m_graphic.getPosition();
}
