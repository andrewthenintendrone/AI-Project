#include "UI2.h"
#include "Renderer.h"
#include "Path.h"
#include "InputManager.h"
std::string getPath();

UI2::UI2()
{
    sf::Vector2u screenSize = Renderer::getInstance()->getWindow().getSize();

    m_rightBar.setSize(sf::Vector2f(100, screenSize.y));
    m_rightBar.setFillColor(sf::Color(0, 0, 0, 128));

    // setup create node option graphic
    m_addTex.loadFromFile(getPath() + "\\resources\\graphics\\ic_add_circle_outline_white_24dp_2x.png");
    m_addSprite.setTexture(m_addTex);
    m_addSprite.setColor(sf::Color::White);
    m_addSprite.setOrigin(sf::Vector2f(24, 24));

    // setup delete node option graphic
    m_removeTex.loadFromFile(getPath() + "\\resources\\graphics\\ic_remove_circle_outline_white_24dp_2x.png");
    m_removeSprite.setTexture(m_removeTex);
    m_removeSprite.setColor(sf::Color::White);
    m_removeSprite.setOrigin(sf::Vector2f(24, 24));

    // setup link node option graphic
    m_linkTex.loadFromFile(getPath() + "\\resources\\graphics\\ic_link_white_24dp_2x.png");
    m_linkSprite.setTexture(m_linkTex);
    m_linkSprite.setColor(sf::Color::White);
    m_linkSprite.setOrigin(sf::Vector2f(24, 24));

    setPosition(sf::Vector2f(screenSize.x - 100, 0));
}

void UI2::update(PathNode* selectedNode)
{

}

void UI2::draw()
{
    Renderer::getInstance()->Draw(&m_rightBar);
    Renderer::getInstance()->Draw(&m_addSprite);
    Renderer::getInstance()->Draw(&m_removeSprite);
    Renderer::getInstance()->Draw(&m_linkSprite);
}

void UI2::setPosition(sf::Vector2f newPosition)
{
    // move dropdown box graphic
    m_rightBar.setPosition(newPosition);

    // move create node option graphic
    m_addSprite.setPosition(m_rightBar.getPosition().x + 50, m_rightBar.getPosition().y + 50);

    // move delete node option graphic
    m_removeSprite.setPosition(m_rightBar.getPosition().x + 50, m_rightBar.getPosition().y + 250);

    // move link node option graphic
    m_linkSprite.setPosition(m_rightBar.getPosition().x + 50, m_rightBar.getPosition().y + 450);
}