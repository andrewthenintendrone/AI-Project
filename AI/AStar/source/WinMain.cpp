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
    // create the window
    Renderer::getInstance()->createWindow(1280, 720);

    // seed the rng
    srand(unsigned(time(NULL)));

    // create a path
    Path path;

    // add 10 nodes to the path in random locations
    for (int x = 0; x < 10; x++)
    {
        path.addNode(sf::Vector2f((float)(rand() % (Renderer::getInstance()->getWindow()->getSize().x - 300) + 50), (float)(rand() % (Renderer::getInstance()->getWindow()->getSize().y - 100) + 50)));
    }

    // main program loop
    while (Renderer::getInstance()->getWindow()->isOpen())
    {
        // update managers
        TIMEMANAGER->update();
        InputManager::getInstance()->update();

        // update and draw path
        Renderer::getInstance()->clearWindow();
        path.update();
        path.draw();
        Renderer::getInstance()->updateWindow();
    }

    return 0;
}