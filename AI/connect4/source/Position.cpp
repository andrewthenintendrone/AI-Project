#include "Position.h"

// constructor resets the grid
Position::Position() : m_grid{ TILESTATE::EMPTY }, m_heights{ 0 }, m_numMoves{ 0 }
{

}

// copy constructor
Position::Position(Position& P)
{
    m_numMoves = P.m_numMoves;

    for (int x = 0; x < WIDTH; x++)
    {
        m_heights[x] = P.m_heights[x];
        for (int y = 0; y < HEIGHT; y++)
        {
            m_grid[x][y] = P.m_grid[x][y];
        }
    }
}

// returns true if a column can be played
bool Position::canPlay(int column) const
{
    return m_heights[column] < HEIGHT;
}

// plays a column
void Position::play(int column)
{
    if (isWinningMove(column))
    {
        m_won = true;
    }
    m_grid[column][m_heights[column]] = (m_numMoves % 2 == 0 ? TILESTATE::RED : TILESTATE::YELLOW);
    m_heights[column]++;
    m_numMoves++;
}

bool Position::isWinningMove(int column) const
{
    TILESTATE current_player = (m_numMoves % 2 == 0 ? TILESTATE::RED : TILESTATE::YELLOW);

    // check for vertical alignments
    if (m_heights[column] >= 3)
    {
        if (m_grid[column][m_heights[column] - 1] == current_player)
        {
            if (m_grid[column][m_heights[column] - 2] == current_player)
            {
                if (m_grid[column][m_heights[column] - 3] == current_player)
                {
                    return true;
                }
            }
        }
    }

    for (int dy = -1; dy <= 1; dy++)
    {
        int nb = 0;
        for (int dx = -1; dx <= 1; dx += 2)
        {
            for (int x = column + dx, y = m_heights[column] + dx * dy; x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT && m_grid[x][y] == current_player; nb++)
            {
                x += dx;
                y += dx*dy;
            }
            if (nb >= 3)
            {
                return true;
            }
        }
    }

    return false;
}

