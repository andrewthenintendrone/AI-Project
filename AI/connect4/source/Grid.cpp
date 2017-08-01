#include "Grid.h"
#include "Renderer.h"
#include "InputManager.h"

Grid::Grid()
{
    // set up grid
    sf::Vector2f screenCenter = Renderer::getInstance()->getWindowSizef() / 2.0f;

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            m_gridTiles[x][y].setPosition(screenCenter.x - (50 * (width - 1)) + (x * 100), screenCenter.y - (50 * (height - 1)) + (y * 100));
        }
    }

    // allow AI to access the grid
    m_AI.setUp(this);
}

void Grid::update()
{
    if (m_playersTurn)
    {
        playerTurn();
    }
    else
    {
        aiTurn();
    }

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            m_gridTiles[x][y].update();
        }
    }
}

// wait for the player to make a valid move
void Grid::playerTurn()
{
    // player has clicked
    if (InputManager::getInstance()->getLeftClick())
    {
        // check all grid squares
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < width; y++)
            {
                // if one has been clicked
                if (InputManager::getInstance()->getHovering(&m_gridTiles[x][y].getRectangleGraphic()))
                {
                    // play that column if possible
                    if (canPlay(x))
                    {
                        play(x);
                        // players turn is over
                        swapTurns();
                    }
                    return;
                }
            }
        }
    }
}

// calculate a good move and play it
void Grid::aiTurn()
{
    m_AI.makeBestMove();
}

void Grid::draw()
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            m_gridTiles[x][y].draw();
        }
    }
}

// returns true if a column can be played
bool Grid::canPlay(int column)
{
    for (int currentRow = height - 1; currentRow >= 0; currentRow--)
    {
        if (m_gridTiles[column][currentRow].getState() == TILESTATE::EMPTY)
        {
            return true;
        }
    }
    return false;
}

// plays a column
void Grid::play(int column)
{
    for (int currentRow = height - 1; currentRow >= 0; currentRow--)
    {
        if (m_gridTiles[column][currentRow].getState() == TILESTATE::EMPTY)
        {
            m_gridTiles[column][currentRow].setState(m_playersTurn ? TILESTATE::RED : TILESTATE::YELLOW);
            return;
        }
    }
}

void Grid::swapTurns()
{
    m_playersTurn = !m_playersTurn;
}
