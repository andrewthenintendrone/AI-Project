#include <Windows.h>
#include "Renderer.h"
#include <string>
#include <stdlib.h>
#include "Path.h"
#include "Edge.h"
#include "PathFinder.h"
#include "InputManager.h"
#include "Path2.h"
#include "UI2.h"

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
    path.addNode(sf::Vector2f((float)(rand() % (Renderer::getInstance()->getWindow().getSize().x - 300) + 50), (float)(rand() % (Renderer::getInstance()->getWindow().getSize().y - 100) + 50)));
    for (int i = 0; i < 10; i++)
    {
        path.addNode(sf::Vector2f((float)(rand() % (Renderer::getInstance()->getWindow().getSize().x - 300) + 50), (float)(rand() % (Renderer::getInstance()->getWindow().getSize().y - 100) + 50)));
    }

    sf::Event event;
    while (Renderer::getInstance()->getWindow().isOpen())
    {
        InputManager::getInstance()->update();
        Renderer::getInstance()->clearWindow();
        path.update();
        path.draw();
        Renderer::getInstance()->updateWindow();
    }

    return 0;
}