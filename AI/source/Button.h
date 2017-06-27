#pragma once
#include "SFML\Graphics.hpp"

class Button
{
public:
    Button();

    void draw();
private:
    sf::RectangleShape graphic;
};