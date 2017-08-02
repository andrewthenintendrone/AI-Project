#pragma once

const int width = 7;
const int height = 6;
static int layers = 0;

enum class TILESTATE { EMPTY, RED, YELLOW };

class Position
{
public:
    Position();
    Position(Position* otherPosition);

    bool canPlay(int column);
    void play(int column);

    bool isWinningMove(int column);
    bool checkWin();
    void unPlay(int column);

    int negaMax(Position position);

    TILESTATE m_tiles[width][height];
    unsigned int m_numMoves = 0;
};