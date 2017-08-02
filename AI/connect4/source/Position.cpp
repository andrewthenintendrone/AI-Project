#include "Position.h"

// constructor resets the grid
Position::Position()
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            m_tiles[x][y] = TILESTATE::EMPTY;
        }
    }
}

// copy constructor
Position::Position(Position* otherPosition)
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            m_tiles[x][y] = otherPosition->m_tiles[x][y];
        }
    }
    m_numMoves = otherPosition->m_numMoves;
}

// returns true if a player has won
bool Position::checkWin()
{
    // only check the player who's turn it is
    TILESTATE stateToCheck = (m_numMoves % 2 == 0 ? TILESTATE::RED : TILESTATE::YELLOW);

    int cumulativeCount = 0;

    // check vertical
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            if (m_tiles[x][y] == stateToCheck)
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
            if (m_tiles[y][x] == stateToCheck)
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
                if (m_tiles[x + d][y + d] == stateToCheck)
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
                if (m_tiles[x - d][y + d] == stateToCheck)
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
bool Position::canPlay(int column)
{
    for (int currentRow = (height - 1); currentRow >= 0; currentRow--)
    {
        if (m_tiles[column][currentRow] == TILESTATE::EMPTY)
        {
            return true;
        }
    }
    return false;
}

bool Position::isWinningMove(int column)
{
    play(column);
    bool hasWon = false;
    if (checkWin())
    {
        hasWon = true;
    }
    unPlay(column);
    return hasWon;
}

// plays a column
void Position::play(int column)
{
    for (int currentRow = (height - 1); currentRow >= 0; currentRow--)
    {
        if (m_tiles[column][currentRow] == TILESTATE::EMPTY)
        {
            m_tiles[column][currentRow] = (m_numMoves % 2 == 0 ? TILESTATE::RED : TILESTATE::YELLOW);
            return;
        }
    }
}

// unplays a column
void Position::unPlay(int column)
{
    for (int currentRow = (height - 1); currentRow >= 0; currentRow--)
    {
        if (m_tiles[column][currentRow] != TILESTATE::EMPTY)
        {
            m_tiles[column][currentRow] = TILESTATE::EMPTY;
            return;
        }
    }
}

int Position::negaMax(Position position)
{
    layers++;
    // check for draw game
    if (m_numMoves == width * height)
    {
        return 0;
    }

    // check if current player can win next move
    for (int x = 0; x < width; x++)
    {
        if (canPlay(x) && isWinningMove(x))
        {
            return (width * height + 1 - m_numMoves) / 2;
        }
    }

    int bestScore = -width * height; // init the best possible score with a lower bound of score.

    for (int x = 0; x < width; x++) // compute the score of all possible next move and keep the best one
    {
        if (canPlay(x))
        {
            Position* P2 = new Position(this);
            P2->play(x);               // It's opponent turn in P2 position after current player plays x column.
            int score = -negaMax(P2); // If current player plays col x, his score will be the opposite of opponent's score after playing col x
            if (score > bestScore) bestScore = score; // keep track of best possible score so far.
            delete P2;
        }
    }

    return bestScore;
}

