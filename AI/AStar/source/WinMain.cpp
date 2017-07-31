#include <Windows.h>
#include "Renderer.h"
#include <string>
#include <stdlib.h>
#include "Path.h"
#include "Edge.h"
#include "PathFinder.h"
#include "InputManager.h"
#include "TimeManager.h"

// returns path to the executable
std::string getPath()
{
    char buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    std::string::size_type pos = std::string(buffer).find_last_of("\\/");
    return std::string(buffer).substr(0, pos);
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int cmdShow)
{
    Renderer::getInstance()->createWindow(1280, 720);

    srand(unsigned(time(NULL)));

    Path path;

    for (int x = 0; x < 10; x++)
    {
        for (int y = 0; y < 10; y++)
        {
            path.addNode(sf::Vector2f(100 * x + 64, 100 + y * 64));
        }
    }

    while (Renderer::getInstance()->getWindow()->isOpen())
    {
        TIMEMANAGER->update();
        InputManager::getInstance()->update();
        Renderer::getInstance()->clearWindow();
        path.update();
        path.draw();
        Renderer::getInstance()->updateWindow();
    }

    return 0;
}