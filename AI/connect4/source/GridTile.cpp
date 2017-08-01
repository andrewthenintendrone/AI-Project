#include "GridTile.h"
#include "Renderer.h"

GridTile::GridTile()
{
    // set up rectangle
    m_rectangleGraphic.setSize(sf::Vector2f(100, 100));
    m_rectangleGraphic.setFillColor(sf::Color(0, 0, 255));
    m_rectangleGraphic.setOrigin(m_rectangleGraphic.getLocalBounds().width / 2, m_rectangleGraphic.getLocalBounds().height / 2);

    // set up circle
    m_circleGraphic.setRadius(45.0f);
    m_circleGraphic.setPointCount(100.0f);
    m_circleGraphic.setFillColor(sf::Color(128, 128, 128));
    m_circleGraphic.setOrigin(m_circleGraphic.getLocalBounds().width / 2, m_circleGraphic.getLocalBounds().height / 2);
}

// sets the position of the GridTile
void GridTile::setPosition(sf::Vector2f& newPosition)
{
    m_rectangleGraphic.setPosition(newPosition);
    m_circleGraphic.setPosition(newPosition);
}

void GridTile::setPosition(float newX, float newY)
{
    setPosition(sf::Vector2f(newX, newY));
}

sf::RectangleShape GridTile::getRectangleGraphic()
{
    return m_rectangleGraphic;
}

sf::Vector2f GridTile::getPosition()
{
    return m_rectangleGraphic.getPosition();
}

TILESTATE GridTile::getState()
{
    return m_tileState;
}

void GridTile::setState(TILESTATE newState)
{
    m_tileState = newState;
}

void GridTile::update()
{
    // check state of tile
    switch (m_tileState)
    {
    case TILESTATE::EMPTY:
        m_circleGraphic.setFillColor(sf::Color(128, 128, 128));
        break;
    case TILESTATE::RED:
        m_circleGraphic.setFillColor(sf::Color(255, 0, 0));
        break;
    case TILESTATE::YELLOW:
        m_circleGraphic.setFillColor(sf::Color(255, 255, 0));
        break;
    default:
        m_circleGraphic.setFillColor(sf::Color(128, 128, 128));
        break;
    }
}

void GridTile::draw()
{
    Renderer::getInstance()->Draw(&m_rectangleGraphic);
    Renderer::getInstance()->Draw(&m_circleGraphic);
}
