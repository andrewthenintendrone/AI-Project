#include "UI.h"
#include "Renderer.h"
#include "InputManager.h"

std::string getPath();

// default constructor sets up
UI::UI()
{
    // setup size and position
    windowSize = Renderer::getInstance()->getWindow()->getSize();

    m_rightBar.setSize(sf::Vector2f((float)barWidth, (float)windowSize.y));
    m_rightBar.setFillColor(sf::Color(0, 0, 0, 128));

    // calculate icon size by dividing wanted size by image size
    float adjustedIconSize = (iconSize / 96.0f);

    // setup create node option graphic
    m_addTex.loadFromFile(getPath() + "\\resources\\graphics\\ic_add_circle_outline_white_24dp.png");
    m_addSprite.setTexture(m_addTex);
    m_addSprite.setScale(adjustedIconSize, adjustedIconSize);
    m_addSprite.setOrigin(m_addSprite.getLocalBounds().width / 2.0f, m_addSprite.getLocalBounds().height / 2.0f);

    // setup delete node option graphic
    m_removeTex.loadFromFile(getPath() + "\\resources\\graphics\\ic_remove_circle_outline_white_24dp.png");
    m_removeSprite.setTexture(m_removeTex);
    m_removeSprite.setScale(adjustedIconSize, adjustedIconSize);
    m_removeSprite.setOrigin(m_removeSprite.getLocalBounds().width / 2.0f, m_removeSprite.getLocalBounds().height / 2.0f);

    // setup link node option graphic
    m_linkTex.loadFromFile(getPath() + "\\resources\\graphics\\ic_share_white_24dp.png");
    m_linkSprite.setTexture(m_linkTex);
    m_linkSprite.setScale(adjustedIconSize, adjustedIconSize);
    m_linkSprite.setOrigin(m_linkSprite.getLocalBounds().width / 2.0f, m_linkSprite.getLocalBounds().height / 2.0f);

    // set UI position to the right of the screen
    setPosition(sf::Vector2f(windowSize.x - barWidth, 0));
}

// update function
void UI::update()
{
    updateUIState();
}

// draw function
void UI::draw()
{
    // draw the bar and all the sprites
    Renderer::getInstance()->Draw(&m_rightBar);
    Renderer::getInstance()->Draw(&m_addSprite);
    Renderer::getInstance()->Draw(&m_removeSprite);
    Renderer::getInstance()->Draw(&m_linkSprite);
}

// sets the position of the UI
void UI::setPosition(sf::Vector2f newPosition)
{
    sf::Vector2u screenSize = Renderer::getInstance()->getWindow()->getSize();

    // move dropdown box graphic
    m_rightBar.setPosition(newPosition);

    // move create node option graphic
    m_addSprite.setPosition((float)m_rightBar.getPosition().x + (barWidth / 2), (float)windowSize.y / 4);

    // move delete node option graphic
    m_removeSprite.setPosition((float)m_rightBar.getPosition().x + (barWidth / 2), (float)windowSize.y / 2);

    // move link node option graphic
    m_linkSprite.setPosition((float)m_rightBar.getPosition().x + (barWidth / 2), (float)windowSize.y * 3 / 4);
}

// returns the current UI mode
UIMODE UI::getUImode()
{
    return m_currentMode;
}

// updates the current UI state
void UI::updateUIState()
{
    // the user is hovering over the add button
    if (InputManager::getInstance()->getHovering(&m_addSprite))
    {
        if (InputManager::getInstance()->getLeftClick())
        {
            // update icon colors and set state to adding
            m_currentMode = UIMODE::ADDING;
            m_addSprite.setColor(sf::Color::Green);
            m_removeSprite.setColor(sf::Color::White);
            m_linkSprite.setColor(sf::Color::White);
        }
    }
    // the user is hovering over the remove button
    else if (InputManager::getInstance()->getHovering(&m_removeSprite))
    {
        if (InputManager::getInstance()->getLeftClick())
        {
            // update icon colors and set state to removing
            m_currentMode = UIMODE::REMOVING;
            m_removeSprite.setColor(sf::Color::Red);
            m_addSprite.setColor(sf::Color::White);
            m_linkSprite.setColor(sf::Color::White);
        }
    }
    // the user is hovering over the link button
    else if (InputManager::getInstance()->getHovering(&m_linkSprite))
    {
        if (InputManager::getInstance()->getLeftClick())
        {
            // update icon colors and set state to linking
            m_currentMode = UIMODE::LINKING;
            m_linkSprite.setColor(sf::Color::Yellow);
            m_addSprite.setColor(sf::Color::White);
            m_removeSprite.setColor(sf::Color::White);
        }
    }

    // right click resets the state to idle
    if (InputManager::getInstance()->getRightClick())
    {
        // update icon colors and set state to idle
        m_currentMode = UIMODE::IDLE;
        m_addSprite.setColor(sf::Color::White);
        m_removeSprite.setColor(sf::Color::White);
        m_linkSprite.setColor(sf::Color::White);
    }
}
