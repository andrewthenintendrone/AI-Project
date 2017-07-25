#include "UI2.h"
#include "Renderer.h"
#include "Path.h"
#include "InputManager.h"
std::string getPath();

UI2::UI2()
{
    windowSize = Renderer::getInstance()->getWindow().getSize();

    m_rightBar.setSize(sf::Vector2f(barWidth, windowSize.y));
    m_rightBar.setFillColor(sf::Color(0, 0, 0, 128));

    float adjustedIconSize = (iconSize / 48.0f);

    // setup create node option graphic
    m_addTex.loadFromFile(getPath() + "\\resources\\graphics\\ic_add_circle_outline_white_24dp_2x.png");
    m_addSprite.setTexture(m_addTex);
    m_addSprite.setScale(adjustedIconSize, adjustedIconSize);
    m_addSprite.setOrigin(m_addSprite.getLocalBounds().width / 2.0f, m_addSprite.getLocalBounds().height / 2.0f);

    // setup delete node option graphic
    m_removeTex.loadFromFile(getPath() + "\\resources\\graphics\\ic_remove_circle_outline_white_24dp_2x.png");
    m_removeSprite.setTexture(m_removeTex);
    m_removeSprite.setScale(adjustedIconSize, adjustedIconSize);
    m_removeSprite.setOrigin(m_removeSprite.getLocalBounds().width / 2.0f, m_removeSprite.getLocalBounds().height / 2.0f);

    // setup link node option graphic
    m_linkTex.loadFromFile(getPath() + "\\resources\\graphics\\ic_link_white_24dp_2x.png");
    m_linkSprite.setTexture(m_linkTex);
    m_linkSprite.setScale(adjustedIconSize, adjustedIconSize);
    m_linkSprite.setOrigin(m_linkSprite.getLocalBounds().width / 2.0f, m_linkSprite.getLocalBounds().height / 2.0f);

    setPosition(sf::Vector2f(windowSize.x - barWidth, 0));
}

void UI2::update()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(Renderer::getInstance()->getWindow());
    sf::Vector2f fMousePos = sf::Vector2f((float)mousePos.x, (float)mousePos.y);

    // which button are we clicking?
    if (m_addSprite.getGlobalBounds().contains(fMousePos))
    {
        m_currentMode = UIMODE::ADDING;
    }
    else if (m_removeSprite.getGlobalBounds().contains(fMousePos))
    {
        m_currentMode = UIMODE::REMOVING;
    }
    else if (m_linkSprite.getGlobalBounds().contains(fMousePos))
    {
        m_currentMode = UIMODE::LINKING;
    }
    else
    {
        m_currentMode = UIMODE::IDLE;
    }
}

void UI2::draw()
{
    switch (m_currentMode)
    {
    case UIMODE::IDLE:
        m_addSprite.setColor(sf::Color::White);
        m_removeSprite.setColor(sf::Color::White);
        m_linkSprite.setColor(sf::Color::White);
        break;
    case UIMODE::ADDING:
        m_addSprite.setColor(sf::Color::Green);
        break;
    case UIMODE::REMOVING:
        m_removeSprite.setColor(sf::Color::Red);
        break;
    case UIMODE::LINKING:
        m_linkSprite.setColor(sf::Color::Yellow);
        break;
    default:
        break;
    }

    Renderer::getInstance()->Draw(&m_rightBar);
    Renderer::getInstance()->Draw(&m_addSprite);
    Renderer::getInstance()->Draw(&m_removeSprite);
    Renderer::getInstance()->Draw(&m_linkSprite);
}

void UI2::setPosition(sf::Vector2f newPosition)
{
    sf::Vector2u screenSize = Renderer::getInstance()->getWindow().getSize();

    // move dropdown box graphic
    m_rightBar.setPosition(newPosition);

    // move create node option graphic
    m_addSprite.setPosition(m_rightBar.getPosition().x + (barWidth / 2), windowSize.y / 4);

    // move delete node option graphic
    m_removeSprite.setPosition(m_rightBar.getPosition().x + (barWidth / 2), windowSize.y / 2);

    // move link node option graphic
    m_linkSprite.setPosition(m_rightBar.getPosition().x + (barWidth / 2), windowSize.y * 3 / 4);
}