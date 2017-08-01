#include "Grid.h"
#include "Renderer.h"
#include "InputManager.h"

std::string getPath();

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

    // set up win text
    m_font.loadFromFile(getPath() + "\\resources\\font\\calibri.ttf");
    m_winText.setFont(m_font);

    // allow AI to access the grid
    m_AI.setUp(this);
}

// waits for the player to make a valid move
void Grid::playerTurn()
{
    // player has clicked
    if (InputManager::getInstance()->getLeftClick())
    {
        // check all grid squares
        for (int x = 0; x < width; x++)
        {
            for (int y = 0; y < height; y++)
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

// calculates a good move and play it
void Grid::aiTurn()
{
    m_AI.makeBestMove();
}

// handles game flow
void Grid::update()
{
    if (checkWin())
    {
        m_winText.setString(std::string("player " + std::string(m_playersTurn ? "2" : "1") + " wins!"));
        m_winText.setCharacterSize(40);
        m_winText.setPosition(20, 20);
        m_winText.setFillColor(sf::Color(255, 255, 255));
        Renderer::getInstance()->Draw(&m_winText);
    }
    else
    {
        if (m_playersTurn)
        {
            playerTurn();
        }
        else
        {
            playerTurn();
        }
    }

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            m_gridTiles[x][y].update();
        }
    }
}

// draws grid tiles
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

// returns true if a player has won
bool Grid::checkWin()
{
    // only check the player who's turn it is
    TILESTATE stateToCheck = (m_playersTurn ? TILESTATE::YELLOW : TILESTATE::RED);

    int cumulativeCount = 0;

    // check vertical
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            if (m_gridTiles[x][y].getState() == stateToCheck)
            {
                cumulativeCount++;
                if (cumulativeCount == 4)
                {
                    return true;
                }
            }
            else
            {
                cumulativeCount = 0;
            }
        }
        cumulativeCount = 0;
    }

    // check horizontal
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            if (m_gridTiles[y][x].getState() == stateToCheck)
            {
                cumulativeCount++;
                if (cumulativeCount == 4)
                {
                    return true;
                }
            }
            else
            {
                cumulativeCount = 0;
            }
        }
        cumulativeCount = 0;
    }

    // check left diagonals
    for (int x = 0; x < width - 3; x++)
    {
        for (int y = 0; y < height - 3; y++)
        {
            for (int d = 0; d < 4; d++)
            {
                if (m_gridTiles[x + d][y + d].getState() == stateToCheck)
                {
                    cumulativeCount++;
                    if (cumulativeCount == 4)
                    {
                        return true;
                    }
                }
                else
                {
                    cumulativeCount = 0;
                }
            }
            cumulativeCount = 0;
        }
    }

    // check right diagonals
    for (int x = width; x >= 3; x--)
    {
        for (int y = 0; y < height - 3; y++)
        {
            for (int d = 0; d < 4; d++)
            {
                if (m_gridTiles[x - d][y + d].getState() == stateToCheck)
                {
                    cumulativeCount++;
                    if (cumulativeCount == 4)
                    {
                        return true;
                    }
                }
                else
                {
                    cumulativeCount = 0;
                }
            }
            cumulativeCount = 0;
        }
    }

    return false;
}

// returns true if a column can be played
bool Grid::canPlay(int column)
{
    for (int currentRow = (height - 1); currentRow >= 0; currentRow--)
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
    for (int currentRow = (height - 1); currentRow >= 0; currentRow--)
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
