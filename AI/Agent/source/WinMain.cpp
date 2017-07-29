#include <Windows.h>
#include "ObjectPool.h"
#include "Renderer.h"
#include "GameObject.h"
#include "InputManager.h"
#include "keyBoardControl.h"
#include "SeekMouse.h"
#include "CopyMousePosition.h"
#include "Pursue.h"
#include "Evade.h"
#include "Wander.h"
#include "Arrive.h"
#include "TimeManager.h"
#include "Character.h"
#include "Wall.h"
#include "Avoid.h"

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

    std::list<Wall*> walls;
    for (int i = 0; i < 10; i++)
    {
        walls.push_back(new Wall);
    }
    std::list<GameObject*> gameobjects;
    for (int i = 0; i < 100; i++)
    {
        GameObject* newGameObject = new GameObject("pikmin_" + pikminTypes[rand() % 5]);
        newGameObject->addBehavior(new Wander);
        newGameObject->addBehavior(new Avoid(walls));
        gameobjects.push_back(newGameObject);
    }

    while (Renderer::getInstance()->getWindow()->isOpen())
    {
        InputManager::getInstance()->update();
        TIMEMANAGER->update();
        Renderer::getInstance()->clearWindow();
        for (auto iter = gameobjects.begin(); iter != gameobjects.end(); iter++)
        {
            (*iter)->update();
            (*iter)->draw();
        }
        for (auto iter = walls.begin(); iter != walls.end(); iter++)
        {
            (*iter)->draw();
        }
        Renderer::getInstance()->updateWindow();
    }

    return 0;
}