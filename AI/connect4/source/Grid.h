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

private:
    GridTile m_gridTiles[numColumns][numRows];
};