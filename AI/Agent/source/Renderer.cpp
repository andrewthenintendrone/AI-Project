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

sf::RenderWindow& Renderer::getWindow()
{
    return window;
}

void Renderer::closeWindow()
{
    window.close();
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