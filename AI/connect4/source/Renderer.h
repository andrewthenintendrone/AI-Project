#pragma once
#include "SFML\Graphics.hpp"

const sf::Color backgroundColor = sf::Color(0, 0, 0);

class Renderer
{
public:
    static Renderer* getInstance();

    bool createWindow(int width, int height);
    void closeWindow();

    sf::RenderWindow* getWindow();
    sf::Vector2f getWindowSizef();
    sf::Vector2u getWindowSizeu();

    void clearWindow();
    void Draw(sf::Drawable* objectToDraw);
    void updateWindow();

private:
    sf::RenderWindow window;
};