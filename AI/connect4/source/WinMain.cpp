#include <Windows.h>
#include "Renderer.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Grid.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow)
{
    // create window
    Renderer::getInstance()->createWindow(1280, 720);

    bool player1Turn = true;

    Grid grid;
    sf::Clock timer;

    while (Renderer::getInstance()->getWindow()->isOpen())
    {
        InputManager::getInstance()->update();
        TimeManager::getInstance()->update();

        Renderer::getInstance()->clearWindow();
        grid.update();
        grid.draw();
        Renderer::getInstance()->updateWindow();
    }

    return 0;
}