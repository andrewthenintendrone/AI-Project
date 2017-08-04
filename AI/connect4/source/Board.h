#pragma once
#include "GridTile.h"
#include "Position.h"

class Grid
{
public:
    Grid();
    Grid(Grid* otherGrid);

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