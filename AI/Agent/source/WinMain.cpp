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

const std::string pikminTypes[5] = { "red", "yellow", "blue", "rock", "winged" };

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

    //srand(unsigned(time(NULL)));

    sf::Vector2u windowSize = Renderer::getInstance()->getWindowSizeu();

    GameObject* dog = new GameObject("dog");
    dog->addBehavior(new KeyboardControl(300.0f));
    dog->addBehavior(new FlipSprite);

    std::list<GameObject*> gameObjects[5];

    // create 50 of each type of pikmin
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            GameObject* newGameObject = new GameObject("fish" + std::to_string(i + 1));
            newGameObject->getAgent()->setPosition(sf::Vector2f((float)(rand() % windowSize.x), (float)(rand() % windowSize.y)));
            newGameObject->getAgent()->setVelocity(getRandomVector(1.0f));
            gameObjects[i].push_back(newGameObject);
        }
        for (std::list<GameObject*>::iterator iter = gameObjects[i].begin(); iter != gameObjects[i].end(); iter++)
        {
            (*iter)->addBehavior(new FlipSprite);
            (*iter)->addBehavior(new WrapScreen);
            (*iter)->addBehavior(new Flee(dog), 0.5f);
            (*iter)->addBehavior(new Flock(&gameObjects[i]));
        }
    }

    while (Renderer::getInstance()->getWindow()->isOpen())
    {
        InputManager::getInstance()->update();
        TIMEMANAGER->update();
        Renderer::getInstance()->clearWindow();
        dog->update();
        dog->draw();

        // update and draw pikmin
        for (int i = 0; i < 5; i++)
        {
            for (std::list<GameObject*>::iterator iter = gameObjects[i].begin(); iter != gameObjects[i].end(); iter++)
            {
                (*iter)->update();
                (*iter)->draw();
            }
        }

        Renderer::getInstance()->updateWindow();
    }

    return 0;
}