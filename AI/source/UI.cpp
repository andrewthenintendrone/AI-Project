#include "UI.h"
#include "Renderer.h"
#include "Path.h"
std::string getPath();

UI::UI()
{
    // setup dropdown box graphic
    m_dropDown.setSize(sf::Vector2f(96, 96));
    m_dropDown.setFillColor(sf::Color::Black);

    // setup create node option graphic
    m_optionCreateIcon.loadFromFile(getPath() + "\\resources\\graphics\\ic_add_circle_outline_white_24dp_2x.png");
    m_optionCreateIconSprite.setTexture(m_optionCreateIcon);
    m_optionCreateIconSprite.setColor(sf::Color::White);

    // setup delete node option graphic
    m_optionDeleteIcon.loadFromFile(getPath() + "\\resources\\graphics\\ic_remove_circle_outline_white_24dp_2x.png");
    m_optionDeleteIconSprite.setTexture(m_optionDeleteIcon);
    m_optionDeleteIconSprite.setColor(sf::Color::White);

    // setup link node option graphic
    m_optionLinkIcon.loadFromFile(getPath() + "\\resources\\graphics\\ic_link_white_24dp_2x.png");
    m_optionLinkIconSprite.setTexture(m_optionLinkIcon);
    m_optionLinkIconSprite.setColor(sf::Color::White);

    setPosition(sf::Vector2f(0, 0));
}

void UI::update(PathNode* selectedNode, bool clicking)
{
    // claer all selections to white
    m_optionCreateIconSprite.setColor(sf::Color::White);
    m_optionDeleteIconSprite.setColor(sf::Color::White);
    m_optionLinkIconSprite.setColor(sf::Color::White);

    // store mouse position
    sf::Vector2f mousePos(sf::Mouse::getPosition(Renderer::getInstance()->getWindow()));

    // light up the selection based on the mouse
    if (m_optionCreateIconSprite.getGlobalBounds().contains(mousePos))
    {
        m_optionCreateIconSprite.setColor(sf::Color::Green);
        if (clicking)
        {
            m_path->addNode(mousePos);
        }
    }
    if (m_optionDeleteIconSprite.getGlobalBounds().contains(mousePos))
    {
        m_optionDeleteIconSprite.setColor(sf::Color::Red);
        if (clicking)
        {
            int x = 0;
        }
    }
    if (m_optionLinkIconSprite.getGlobalBounds().contains(mousePos))
    {
        m_optionLinkIconSprite.setColor(sf::Color(128, 128, 128, 255));
        if (clicking)
        {
            int x = 0;
        }
    }
}

void UI::draw()
{
    if (isVisible)
    {
        Renderer::getInstance()->Draw(&m_dropDown);
        Renderer::getInstance()->Draw(&m_optionCreateIconSprite);
        Renderer::getInstance()->Draw(&m_optionDeleteIconSprite);
        Renderer::getInstance()->Draw(&m_optionLinkIconSprite);
    }
}

void UI::setPosition(sf::Vector2f newPosition)
{
    // move dropdown box graphic
    m_dropDown.setPosition(newPosition);

    // move create node option graphic
    m_optionCreateIconSprite.setPosition(m_dropDown.getPosition().x, m_dropDown.getPosition().y);

    // move delete node option graphic
    m_optionDeleteIconSprite.setPosition(m_dropDown.getPosition().x + 48, m_dropDown.getPosition().y);

    // move link node option graphic
    m_optionLinkIconSprite.setPosition(m_dropDown.getPosition().x + 24, m_dropDown.getPosition().y + 48);
}

void UI::setPath(Path* newPath)
{
    m_path = newPath;
}

sf::FloatRect UI::getBounds()
{
    return m_dropDown.getGlobalBounds();
}