#include <Windows.h>
#include "Renderer.h"
#include <string>
#include <stdlib.h>
#include "Path.h"
#include "Edge.h"
#include "PathFinder.h"
#include "InputManager.h"
#include "PathNode2.h"
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

    // Path path;

    UI2 gui;
    std::list<PathNode2*> pathNodes;
    for (int i = 0; i < 100; i++)
    {
        pathNodes.push_back(new PathNode2(sf::Vector2f(rand() % Renderer::getInstance()->getWindow().getSize().x, rand() % Renderer::getInstance()->getWindow().getSize().y)));
    }

    //// add nodes
    //for (unsigned int x = 0; x < 10; x++)
    //{
    //    path.addNode(sf::Vector2f(100 + x * 100.0f, 100.0f));
    //}
    //for (unsigned int x = 0; x < 10; x++)
    //{
    //    if (x != 9)
    //    {
    //        PathNode* firstNode = path.getNode(x);
    //        PathNode* secondNode = path.getNode(x + 1);
    //        path.addEdge(firstNode, secondNode);
    //    }
    //}

    //PathFinder pMan(&path);

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

        InputManager::getInstance()->update(event);
        Renderer::getInstance()->clearWindow();
        //path.update();
        //path.draw();
        //pMan.Update();
        for (auto iter = pathNodes.begin(); iter != pathNodes.end(); iter++)
        {
            (*iter)->draw();
        }
        gui.draw();
        Renderer::getInstance()->updateWindow();
    }

    return 0;
}