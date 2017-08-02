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
}

Grid::Grid(Grid* otherGrid)
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            m_gridTiles[x][y] = otherGrid->m_gridTiles[x][y];
        }
    }
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
                    if (m_position.canPlay(x))
                    {
                        m_position.play(x);
                        // players turn is over
                        m_position.m_numMoves++;
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
    m_position.play(m_position.negaMax(m_position));
}

// handles game flow
void Grid::update()
{
    if (m_position.checkWin())
    {
        m_winText.setString(std::string("player " + std::string(m_position.m_numMoves % 2 == 0 ? "2" : "1") + " wins!"));
        m_winText.setCharacterSize(40);
        m_winText.setPosition(20, 20);
        m_winText.setFillColor(sf::Color(255, 255, 255));
        Renderer::getInstance()->Draw(&m_winText);
    }
    else
    {
        if (m_position.m_numMoves % 2 == 0)
        {
            playerTurn();
        }
        else
        {
            aiTurn();
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
            m_gridTiles[x][y].draw(m_position.m_tiles[x][y]);
        }
    }
}
