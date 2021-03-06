#pragma once
#include "SFML\Graphics.hpp"

const sf::Color backgroundColor = sf::Color(128, 128, 128);

class Renderer
{
public:

    static Renderer* getInstance();

    void createWindow(int width, int height);
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