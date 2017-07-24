#include <Windows.h>
#include "ObjectPool.h"
#include "Renderer.h"
#include "GameObject.h"
#include "keyBoardControl.h"
#include "moveToMouse.h"
#include "CopyMousePosition.h"
#include "Flock.h"
#include "Seek.h"
#include "TimeManager.h"

const std::string pikminTypes[5] = { "red", "yellow", "blue", "rock", "pink" };

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

    ObjectPool::getInstance()->createObject("player")->setSprite("olimar")->addBehavior(new copyMousePosition);
    ObjectPool::getInstance()->createObject("follower0")->setSprite("pikmin_" + pikminTypes[rand() % 5])->addBehavior(new Flock(ObjectPool::getInstance()->getObject("player")));
    for (int i = 1; i < 25; i++)
    {
        ObjectPool::getInstance()->createObject("follower" + std::to_string(i))->setSprite("pikmin_" + pikminTypes[rand() % 5])->addBehavior(new Flock(ObjectPool::getInstance()->getObject("player")));
    }

    srand(unsigned(time(NULL)));

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
        ObjectPool::getInstance()->updateAllObjects();
        ObjectPool::getInstance()->drawAllObjects();
        Renderer::getInstance()->updateWindow();
    }

    return 0;
}