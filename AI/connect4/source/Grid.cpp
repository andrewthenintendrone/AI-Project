#include "Grid.h"
#include "Renderer.h"
#include "InputManager.h"

Grid::Grid()
{
    // set up grid
    sf::Vector2f screenCenter = Renderer::getInstance()->getWindowSizef() / 2.0f;

    for (int x = 0; x < numColumns; x++)
    {
        for (int y = 0; y < numRows; y++)
        {
            m_gridTiles[x][y].setPosition(screenCenter.x - (50 * (numColumns - 1)) + (x * 100), screenCenter.y - (50 * (numRows - 1)) + (y * 100));
        }
    }
}

void Grid::update()
{
    if (InputManager::getInstance()->getLeftClick())
    {
        sf::Vector2f mousePos = InputManager::getInstance()->getMousePosf();
        for (int x = 0; x < numColumns; x++)
        {
            for (int y = 0; y < numRows; y++)
            {
                if (InputManager::getInstance()->getHovering(&m_gridTiles[x][y].getRectangleGraphic()))
                {
                    int placement = getPlacement(x);

                    if (placement != -1)
                    {
                        m_gridTiles[x][placement].setState(player1Turn ? TILESTATE::RED : TILESTATE::YELLOW);
                        player1Turn = !player1Turn;
                        break;
                    }
                }
            }
        }
    }

    for (int x = 0; x < numColumns; x++)
    {
        for (int y = 0; y < numRows; y++)
        {
            m_gridTiles[x][y].update();
        }
    }
}

void Grid::draw()
{
    for (int x = 0; x < numColumns; x++)
    {
        for (int y = 0; y < numRows; y++)
        {
            m_gridTiles[x][y].draw();
        }
    }
}

// returns the lowest point that a tile can be placed or -1 if there is no availible spot
int Grid::getPlacement(int columnToCheck)
{
    for (int currentColumn = numRows - 1; currentColumn >= 0; currentColumn--)
    {
        if (m_gridTiles[columnToCheck][currentColumn].getState() == TILESTATE::EMPTY)
        {
            return currentColumn;
        }
    }
    return -1;
}
