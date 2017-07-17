#include <Windows.h>
#include "Renderer.h"
#include <string>
#include "ObjectPool.h"
#include "TimeManager.h"
#include <stdlib.h>
#include <time.h>
#include "keyBoardControl.h"
#include "Seek.h"
#include "Flock.h"
#include "Path.h"
#include "Edge.h"
#include "Pi.h"

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
    float pi = Pi();
    Renderer::getInstance()->createWindow(1280, 720);

    srand(unsigned(time(NULL)));

    Path path;

    for (unsigned int i = 0; i < 10; i++)
    {
        path.addNode(sf::Vector2f((float)(rand() % Renderer::getInstance()->getWindow().getSize().x), (float)(rand() % Renderer::getInstance()->getWindow().getSize().y)));
    }

    for (unsigned int i = 0; i < 10; i++)
    {
        PathNode* firstNode = path.getNode(rand() % 10);
        PathNode* secondNode = path.getNode(rand() % 10);
        while (firstNode == secondNode)
        {
            secondNode = path.getNode(rand() % 10);
        }
        path.addEdge(firstNode, secondNode);
    }

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

        TIMEMANAGER->update();
        Renderer::getInstance()->clearWindow();
        path.update(event);
        path.draw();
        Renderer::getInstance()->updateWindow();
    }

    return 0;
}