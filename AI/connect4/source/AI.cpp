#include "AI.h"
#include "Grid.h"

void AI::setUp(Grid* newGrid)
{
    m_grid = newGrid;
}

void AI::makeBestMove()
{
    // this will get better
    int move = rand() % width;

    while (!m_grid->canPlay(move))
    {
        move = rand() % width;
    }
    m_grid->play(move);
    m_grid->swapTurns();
}

void AI::updatePosition(int newMove)
{
    m_position.push_back(newMove);
}
