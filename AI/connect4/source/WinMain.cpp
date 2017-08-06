#include <Windows.h>
#include "Renderer.h"
#include "InputManager.h"
#include "Board.h"
#include <stdio.h>
#include <cstdlib>
#include <time.h>

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
    srand(unsigned (time(NULL)));

    // create board
    Board grid;

    while (Renderer::getInstance()->getWindow()->isOpen())
    {
        InputManager::getInstance()->update();

        Renderer::getInstance()->clearWindow();
        grid.update();
        grid.draw();
        Renderer::getInstance()->updateWindow();
    }

    return 0;
}