#pragma once
#include "GridTile.h"
#include "Position.h"
#include "AI.h"

class Board
{
public:
    Board();

    void playerTurn();
    void aiTurn();

    void update();
    void draw();

private:
    Position m_position;
    GridTile m_gridTiles[Position::WIDTH][Position::HEIGHT];

    sf::Font m_font;
    sf::Text m_winText;
};