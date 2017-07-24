#include <Windows.h>
#include "Renderer.h"
#include <string>
#include <stdlib.h>
#include "Path.h"
#include "Edge.h"
#include "PathFinder.h"

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

    for (unsigned int y = 0; y < 5; y++)
    {
        for (unsigned int x = 0; x < 10; x++)
        {
            path.addNode(sf::Vector2f(100 + x * 100.0f, 100 + y * 100.0f));
        }
    }

    for (unsigned int y = 0; y < 5; y++)
    {
        for (unsigned int x = 0; x < 10; x++)
        {
            if ((x * 5 + y + 1) % 10 != 0)
            {
                PathNode* firstNode = path.getNode(x * 5 + y);
                PathNode* secondNode = path.getNode(x * 5 + y + 1);
                path.addEdge(firstNode, secondNode);
            }
        }
    }

    PathFinder pMan;

    while (Renderer::getInstance()->getWindow().isOpen())
    {
        sf::Event event;
        while (Renderer::getInstance()->getWindow().pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                Renderer::getInstance()->closeWindow();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                Renderer::getInstance()->closeWindow();
            }
        }

        Renderer::getInstance()->clearWindow();
        path.update(event);
        path.draw();
        pMan.Update();
        Renderer::getInstance()->updateWindow();
    }

    return 0;
}