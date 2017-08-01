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

    Character player;
    player.addBehavior(new KeyboardControl(350.0f));
    player.addBehavior(new WrapScreen);

    // create 50 red pikmin
    std::list<GameObject*> redPikmin;
    for (int i = 0; i < 50; i++)
    {
        GameObject* newRedPikmin = new GameObject("pikmin_red");
        newRedPikmin->getAgent()->setPosition(sf::Vector2f((float)(rand() % windowSize.x), (float)(rand() % windowSize.y)));
        newRedPikmin->getAgent()->setVelocity(getRandomVector(1.0f));
        redPikmin.push_back(newRedPikmin);
    }
    for (auto iter = redPikmin.begin(); iter != redPikmin.end(); iter++)
    {
        (*iter)->addBehavior(new Flock(&redPikmin, 300.0f));
        (*iter)->addBehavior(new WrapScreen);
    }

    // create 50 blue pikmin
    std::list<GameObject*> bluePikmin;
    for (int i = 0; i < 50; i++)
    {
        GameObject* newBluePikmin = new GameObject("pikmin_blue");
        newBluePikmin->getAgent()->setPosition(sf::Vector2f((float)(rand() % windowSize.x), (float)(rand() % windowSize.y)));
        newBluePikmin->getAgent()->setVelocity(getRandomVector(1.0f));
        bluePikmin.push_back(newBluePikmin);
    }
    for (auto iter = bluePikmin.begin(); iter != bluePikmin.end(); iter++)
    {
        (*iter)->addBehavior(new Flock(&bluePikmin, 300.0f));
        (*iter)->addBehavior(new WrapScreen);
    }

    // create 50 yellow pikmin
    std::list<GameObject*> yellowPikmin;
    for (int i = 0; i < 50; i++)
    {
        GameObject* newYellowPikmin = new GameObject("pikmin_yellow");
        newYellowPikmin->getAgent()->setPosition(sf::Vector2f((float)(rand() % windowSize.x), (float)(rand() % windowSize.y)));
        newYellowPikmin->getAgent()->setVelocity(getRandomVector(1.0f));
        yellowPikmin.push_back(newYellowPikmin);
    }
    for (auto iter = yellowPikmin.begin(); iter != yellowPikmin.end(); iter++)
    {
        (*iter)->addBehavior(new Flock(&yellowPikmin, 300.0f));
        (*iter)->addBehavior(new WrapScreen);
    }

    // create 50 rock pikmin
    std::list<GameObject*> rockPikmin;
    for (int i = 0; i < 50; i++)
    {
        GameObject* newRockPikmin = new GameObject("pikmin_rock");
        newRockPikmin->getAgent()->setPosition(sf::Vector2f((float)(rand() % windowSize.x), (float)(rand() % windowSize.y)));
        newRockPikmin->getAgent()->setVelocity(getRandomVector(1.0f));
        rockPikmin.push_back(newRockPikmin);
    }
    for (auto iter = rockPikmin.begin(); iter != rockPikmin.end(); iter++)
    {
        (*iter)->addBehavior(new Flock(&rockPikmin, 300.0f));
        (*iter)->addBehavior(new WrapScreen);
    }

    // create 50 winged pikmin
    std::list<GameObject*> wingedPikmin;
    for (int i = 0; i < 50; i++)
    {
        GameObject* newWingedPikmin = new GameObject("pikmin_winged");
        newWingedPikmin->getAgent()->setPosition(sf::Vector2f((float)(rand() % windowSize.x), (float)(rand() % windowSize.y)));
        newWingedPikmin->getAgent()->setVelocity(getRandomVector(1.0f));
        wingedPikmin.push_back(newWingedPikmin);
    }
    for (auto iter = wingedPikmin.begin(); iter != wingedPikmin.end(); iter++)
    {
        (*iter)->addBehavior(new Flock(&wingedPikmin, 300.0f));
        (*iter)->addBehavior(new WrapScreen);
    }

    while (Renderer::getInstance()->getWindow()->isOpen())
    {
        InputManager::getInstance()->update();
        TIMEMANAGER->update();
        Renderer::getInstance()->clearWindow();
        player.update();
        player.draw();

        // update and draw red pikmin
        for (auto iter = std::next(redPikmin.begin()); iter != redPikmin.end(); iter++)
        {
            (*iter)->update();
            (*iter)->draw();
        }

        // update and draw blue pikmin
        for (auto iter = std::next(bluePikmin.begin()); iter != bluePikmin.end(); iter++)
        {
            (*iter)->update();
            (*iter)->draw();
        }

        // update and draw yellow pikmin
        for (auto iter = std::next(yellowPikmin.begin()); iter != yellowPikmin.end(); iter++)
        {
            (*iter)->update();
            (*iter)->draw();
        }

        // update and draw rock pikmin
        for (auto iter = std::next(rockPikmin.begin()); iter != rockPikmin.end(); iter++)
        {
            (*iter)->update();
            (*iter)->draw();
        }

        // update and draw winged pikmin
        for (auto iter = std::next(wingedPikmin.begin()); iter != wingedPikmin.end(); iter++)
        {
            (*iter)->update();
            (*iter)->draw();
        }

        Renderer::getInstance()->updateWindow();
    }

    return 0;
}