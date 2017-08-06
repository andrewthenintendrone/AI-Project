#include "Renderer.h"

// there is only ever one Renderer
Renderer* Renderer::getInstance()
{
    static Renderer renderer;
    return &renderer;
}

// creates a window of a specified size
void Renderer::createWindow(int width, int height)
{
    // turn on anti-aliasing
    sf::ContextSettings contextSettings;
    contextSettings.antialiasingLevel = 16;

    // create the window
    window.create(sf::VideoMode(width, height), "AI demo", sf::Style::Titlebar | sf::Style::Close, contextSettings);
}

// close the window
void Renderer::closeWindow()
{
    window.close();
}

// return a pointer to the window
sf::RenderWindow* Renderer::getWindow()
{
    return &window;
}

// return an sf::Vector2f of the size of the window
sf::Vector2f Renderer::getWindowSizef()
{
    return sf::Vector2f(window.getSize());
}

// return an sf::Vector2u of the size of the window
sf::Vector2u Renderer::getWindowSizeu()
{
    return window.getSize();
}

// clear the window to the backgound color (used bfore everything is drawn)
void Renderer::clearWindow()
{
    window.clear(backgroundColor);
}

// draw the specified graphic onto the window
void Renderer::Draw(sf::Drawable* objectToDraw)
{
    window.draw(*objectToDraw);
}

// displays the window (used after everything has been drawn)
void Renderer::updateWindow()
{
    window.display();
}