#include <Windows.h>
#include "ObjectPool.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Behaviors.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Character.h"
#include "Wall.h"
#include "VectorMaths.h"

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

    sf::Vector2u windowSize = Renderer::getInstance()->getWindowSizeu();

    std::list<GameObject*> gameObjects;

    for (int i = 0; i < 100; i++)
    {
        GameObject* newGameObject = new GameObject("pikmin_" + pikminTypes[rand() % 5]);
        newGameObject->getAgent()->setPosition(sf::Vector2f(rand() % windowSize.x, rand() % windowSize.y));
        newGameObject->getAgent()->setVelocity(getRandomVector(1.0f));
        gameObjects.push_back(newGameObject);
    }
    for (auto iter = std::next(gameObjects.begin()); iter != gameObjects.end(); iter++)
    {
        (*iter)->addBehavior(new Flock(gameObjects));
    }

    while (Renderer::getInstance()->getWindow()->isOpen())
    {
        InputManager::getInstance()->update();
        TIMEMANAGER->update();
        Renderer::getInstance()->clearWindow();
        for (auto iter = std::next(gameObjects.begin()); iter != gameObjects.end();)
        {
            (*iter)->update();
            (*iter)->draw();
            if ((*iter)->getAgent()->getPosition().x > 1280)
            {
                iter = gameObjects.erase(iter);
                GameObject* newGameObject = new GameObject("pikmin_" + pikminTypes[rand() % 5]);
                newGameObject->getAgent()->setPosition(sf::Vector2f(rand() % windowSize.x, rand() % windowSize.y));
                newGameObject->getAgent()->setVelocity(getRandomVector(1.0f));
                newGameObject->addBehavior(new Flock(gameObjects));
                gameObjects.push_back(newGameObject);
            }
            else
            {
                iter++;
            }
        }
        Renderer::getInstance()->updateWindow();
    }

    return 0;
}