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
