#include "PathNode2.h"
#include "Renderer.h"

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

}

void PathNode2::draw()
{
    Renderer::getInstance()->Draw(&m_graphic);
}