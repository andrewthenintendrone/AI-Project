#pragma once
#include "GridTile.h"
#include "AI.h"

const int width = 7;
const int height = 6;

class Grid
{
public:
    Grid();

    void playerTurn();
    void aiTurn();

    void update();
    void draw();

    bool checkWin();

    bool canPlay(int column);
    void play(int column);

    void swapTurns();

private:
    GridTile m_gridTiles[width][height];
    bool m_playersTurn = true;

    sf::Font m_font;
    sf::Text m_winText;
    AI m_AI;
};