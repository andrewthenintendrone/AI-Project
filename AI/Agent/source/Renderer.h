#pragma once
#include "SFML\Graphics.hpp"

const sf::Color backgroundColor = sf::Color(28, 32, 44);

class Renderer
{
public:
    static Renderer* getInstance();
    bool createWindow(int width, int height);
    sf::RenderWindow& getWindow();
    void closeWindow();

    void clearWindow();
    void Draw(sf::Drawable* objectToDraw);
    void updateWindow();

private:
    sf::RenderWindow window;
};