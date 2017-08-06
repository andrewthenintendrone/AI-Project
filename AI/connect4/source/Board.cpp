#include "Board.h"
#include "Renderer.h"
#include "InputManager.h"

std::string getPath();

Board::Board()
{
    // set up grid
    sf::Vector2f screenCenter = Renderer::getInstance()->getWindowSizef() / 2.0f;

    for (int x = 0; x < Position::WIDTH; x++)
    {
        for (int y = 0; y < Position::HEIGHT; y++)
        {
            m_gridTiles[x][y].setPosition(screenCenter.x + (50 * (Position::WIDTH - 1)) - (x * 100), screenCenter.y + (50 * (Position::HEIGHT - 1)) - (y * 100));
        }
    }

    // set up win text
    m_font.loadFromFile(getPath() + "\\resources\\font\\calibri.ttf");
    m_winText.setFont(m_font);
}

// waits for the player to make a valid move
void Board::playerTurn()
{
    // player has clicked
    if (InputManager::getInstance()->getLeftClick())
    {
        // check all grid squares
        for (int x = 0; x < Position::WIDTH; x++)
        {
            for (int y = 0; y < Position::HEIGHT; y++)
            {
                // if one has been clicked
                if (InputManager::getInstance()->getHovering(&m_gridTiles[x][y].getRectangleGraphic()))
                {
                    // play that column if possible
                    if (m_position.canPlay(x))
                    {
                        m_position.play(x);
                    }
                    return;
                }
            }
        }
    }
}

// calculates a good move and play it
void Board::aiTurn()
{
    m_position.play(AI::pickGoodMove(m_position));
}

// handles game flow
void Board::update()
{
    // if someone has won only draw win text
    if (m_position.m_won == true)
    {
        m_winText.setString(std::string("player " + std::string(m_position.m_numMoves % 2 == 0 ? "2" : "1") + " wins!"));
        m_winText.setCharacterSize(40);
        m_winText.setPosition(20, 20);
        m_winText.setFillColor(sf::Color(255, 255, 255));
        Renderer::getInstance()->Draw(&m_winText);
    }
    // if the game has reached the maximum number of moves it is a draw
    else if (m_position.m_numMoves == Position::WIDTH * Position::HEIGHT)
    {
        m_winText.setString(std::string("draw game..."));
        m_winText.setCharacterSize(40);
        m_winText.setPosition(20, 20);
        m_winText.setFillColor(sf::Color(255, 255, 255));
        Renderer::getInstance()->Draw(&m_winText);
    }
    // otherwise continue game flow
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
void Board::draw()
{
    for (int x = 0; x < Position::WIDTH; x++)
    {
        for (int y = 0; y < Position::HEIGHT; y++)
        {
            m_gridTiles[x][y].draw(m_position.m_grid[x][y]);
        }
    }
}
