#pragma once

enum class TILESTATE { EMPTY, RED, YELLOW };

class Position
{
public:
    static const int WIDTH = 7;
    static const int HEIGHT = 6;

    Position();

    bool canPlay(int column) const;
    void play(int column);

    bool isWinningMove(int column) const;

    TILESTATE m_grid[WIDTH][HEIGHT];
    int m_heights[WIDTH];
    unsigned int m_numMoves = 0;
    bool m_won = false;
};