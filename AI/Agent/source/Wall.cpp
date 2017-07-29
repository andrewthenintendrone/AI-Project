#include "Wall.h"
#include "Renderer.h"

Wall::Wall(float width, float height)
{
    m_wallGraphic.setFillColor(sf::Color(128, 0, 255));
    m_wallGraphic.setOutlineColor(sf::Color::Black);
    m_wallGraphic.setOutlineThickness(5.0f);
    m_wallGraphic.setSize(sf::Vector2f(width - 10, height - 10));
    m_wallGraphic.setOrigin(m_wallGraphic.getLocalBounds().width / 2, m_wallGraphic.getLocalBounds().height / 2);
    m_wallGraphic.setPosition((float)(rand() % (int)(Renderer::getInstance()->getWindowSizef().x - width * 2) + width), (float)(rand() % (int)(Renderer::getInstance()->getWindowSizef().y - height * 2) + height));
}

Wall::~Wall()
{

}

sf::Vector2f Wall::getPosition()
{
    return m_wallGraphic.getPosition();
}

sf::FloatRect Wall::getBounds()
{
    return m_wallGraphic.getGlobalBounds();
}

void Wall::draw()
{
    Renderer::getInstance()->Draw(&m_wallGraphic);
}
