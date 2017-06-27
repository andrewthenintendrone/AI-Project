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

sf::Font g_font;

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

    g_font.loadFromFile(getPath() + "\\resources\\font\\comic.ttf");

    Path path;

    path.addNode(sf::Vector2f(100, 100));
    path.addNode(sf::Vector2f(300, 100));
    path.addNode(sf::Vector2f(300, 275));
    path.addNode(sf::Vector2f(300, 400));
    path.addNode(sf::Vector2f(200, 510));
    path.addNode(sf::Vector2f(100, 400));

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
        path.draw();
        Renderer::getInstance()->updateWindow();
    }

    return 0;
}