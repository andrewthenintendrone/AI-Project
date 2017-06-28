#include "PathMenu.h"
#include "Renderer.h"


PathMenu::PathMenu(sf::Font& newFont)
{
    sf::Text addNodeText;
    addNodeText.setFont(newFont);
    addNodeText.setPosition(25, 695);
    addNodeText.setFillColor(sf::Color::White);
    addNodeText.setCharacterSize(16);
    m_texts.push_back(addNodeText);
}

void PathMenu::draw()
{
    for (std::vector<sf::Text>::iterator iter = m_texts.begin(); iter != m_texts.end(); iter++)
    {
        Renderer::getInstance()->Draw(iter._Ptr);
    }
}