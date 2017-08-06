#include "AI.h"
#include <cstdlib>

namespace AI
{
    // returns a good move
    // a move is good if
    // a. it wins the game
    // b. it stops the opponent winning the game
    // if there is no good move return a random move
    int pickGoodMove(Position& P)
    {
        // win if possible
        for (int x = 0; x < Position::WIDTH; x++)
        {
            if (P.canPlay(x) && P.isWinningMove(x))
            {
                return x;
            }
        }

        // block player if possible
        Position P2(P);
        P2.m_numMoves++;

        for (int x = 0; x < Position::WIDTH; x++)
        {
            if (P2.canPlay(x) && P2.isWinningMove(x))
            {
                return x;
            }
        }

        // otherwise play a random column
        int randomColumn = rand() % Position::WIDTH;
        do
        {
            randomColumn = rand() % Position::WIDTH;
        } while (!P.canPlay(randomColumn));

        return randomColumn;
    }
}
