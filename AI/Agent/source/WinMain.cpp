#include <Windows.h>
#include "ObjectPool.h"
#include "Renderer.h"
#include "GameObject.h"
#include "InputManager.h"
#include "keyBoardControl.h"
#include "moveToMouse.h"
#include "CopyMousePosition.h"
#include "Seek.h"
#include "Wander.h"
#include "TimeManager.h"
#include "Character.h"

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

    srand(unsigned(time(NULL)));

    Character player;
    player.addBehavior(new moveToMouse(200.0f));

    GameObject follower("pikmin_" + pikminTypes[rand() % 5]);
    follower.getAgent()->setPosition(sf::Vector2f(300.0f, 300.0f));
    follower.addBehavior(new Wander());

    while (Renderer::getInstance()->getWindow()->isOpen())
    {
        InputManager::getInstance()->update();
        TIMEMANAGER->update();
        Renderer::getInstance()->clearWindow();

        player.update();
        player.draw();

        follower.update();
        follower.draw();
        Renderer::getInstance()->updateWindow();
    }

    return 0;
}