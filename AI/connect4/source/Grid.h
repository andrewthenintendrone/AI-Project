#pragma once
#include "GridTile.h"

const int numColumns = 7;
const int numRows = 6;

class Grid
{
public:
    Grid();

    void update();
    void draw();

    int getPlacement(int columnToCheck);

private:
    GridTile m_gridTiles[numColumns][numRows];
    bool player1Turn = true;
};