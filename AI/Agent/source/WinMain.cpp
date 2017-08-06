#include <Windows.h>
#include "Renderer.h"
#include "GameObject.h"
#include "Behaviors.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "Wall.h"
#include "VectorMaths.h"

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
    // create window
    Renderer::getInstance()->createWindow(1280, 720);

    // seed rng
    srand(unsigned(time(NULL)));

    // get window size
    sf::Vector2u windowSize = Renderer::getInstance()->getWindowSizeu();

    // create dog GameObject that is controlled by keyboard
    GameObject dog("dog");
    dog.addBehavior(new KeyboardControl(300.0f));
    dog.addBehavior(new FlipSprite);
    dog.getAgent()->setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f));

    // create character GameObject that Seeks towards the mouse
    GameObject character;
    character.addBehavior(new SeekMouse);
    character.addBehavior(new DrawCharacterSprite);
    character.getAgent()->setPosition(sf::Vector2f(windowSize.x / 4.0f, windowSize.y / 4.0f));

    // create 5 lists of GameObjects
    std::list<GameObject*> gameObjects[7];

    for (int i = 0; i < 7; i++)
    {
        // add 50 of each type of fish to each list
        for (int j = 0; j < 50; j++)
        {
            GameObject* newGameObject = new GameObject("fish" + std::to_string(i + 1));
            newGameObject->getAgent()->setPosition(sf::Vector2f((float)(rand() % windowSize.x), (float)(rand() % windowSize.y)));
            newGameObject->getAgent()->setVelocity(getRandomVector(1.0f));
            gameObjects[i].push_back(newGameObject);
        }

        // add the following behaviors to the fish
        // 1. Flip the sprite based on the direction of travel
        // 2. Wrap around the edges of the screen
        // 3. Flee the dog with a weight of 0.5
        // 4. Flock with the other members of the list
        for (std::list<GameObject*>::iterator iter = gameObjects[i].begin(); iter != gameObjects[i].end(); iter++)
        {
            (*iter)->addBehavior(new FlipSprite);
            (*iter)->addBehavior(new WrapScreen);
            (*iter)->addBehavior(new Flee(&dog), 0.5f);
            (*iter)->addBehavior(new Flock(&gameObjects[i]));
        }
    }

    while (Renderer::getInstance()->getWindow()->isOpen())
    {
        TIMEMANAGER->update();
        InputManager::getInstance()->update();

        Renderer::getInstance()->clearWindow();

        // update and draw the character
        character.update();
        character.draw();

        // update and draw the dog
        dog.update();
        dog.draw();

        // update and draw all the fish
        for (int i = 0; i < 7; i++)
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