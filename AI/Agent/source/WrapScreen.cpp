#include "WrapScreen.h"
#include "Renderer.h"
#include "GameObject.h"

// store window size in the constructor
WrapScreen::WrapScreen()
{
    m_windowSize = Renderer::getInstance()->getWindowSizef();
}

sf::Vector2f WrapScreen::update()
{
    // only check position once
    sf::Vector2f pos = m_myAgent->getPosition();

    if (pos.x < 0)
    {
        m_myAgent->setPosition(sf::Vector2f(m_windowSize.x, pos.y));
    }
    else if (pos.x > m_windowSize.x)
    {
        m_myAgent->setPosition(sf::Vector2f(0, pos.y));
    }

    if (pos.y < 0)
    {
        m_myAgent->setPosition(sf::Vector2f(pos.x, m_windowSize.y));
    }
    else if (pos.y > m_windowSize.y)
    {
        m_myAgent->setPosition(sf::Vector2f(pos.x, 0));
    }

    return sf::Vector2f(0, 0);
}
