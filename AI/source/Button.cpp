#include "Button.h"
#include "Renderer.h"

Button::Button()
{
    graphic.setSize(sf::Vector2f(300, 185));
}

void Button::draw()
{
    Renderer::getInstance()->Draw(&graphic);
}