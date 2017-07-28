#include "Renderer.h"

Renderer* Renderer::getInstance()
{
    static Renderer renderer;
    return &renderer;
}

bool Renderer::createWindow(int width, int height)
{
    sf::ContextSettings contextSettings;
    contextSettings.antialiasingLevel = 16;
    window.create(sf::VideoMode(width, height), "AI demo", sf::Style::Titlebar | sf::Style::Close, contextSettings);
    return true;
}

void Renderer::closeWindow()
{
    window.close();
}

sf::RenderWindow* Renderer::getWindow()
{
    return &window;
}

sf::Vector2f Renderer::getWindowSizef()
{
    return sf::Vector2f(window.getSize());
}

sf::Vector2u Renderer::getWindowSizeu()
{
    return window.getSize();
}

void Renderer::clearWindow()
{
    window.clear(backgroundColor);
}

void Renderer::Draw(sf::Drawable* objectToDraw)
{
    window.draw(*objectToDraw);
}

void Renderer::updateWindow()
{
    window.display();
}