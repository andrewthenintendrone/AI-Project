#pragma once
#include "GameObject.h"

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