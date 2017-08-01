#pragma once
#include "SFML\Graphics.hpp"
#include <list>

class Grid;

class AI
{
public:
    void setUp(Grid* newGrid);
    void makeBestMove();
    void updatePosition(int newMove);

private:
    std::list<int> m_position;
    Grid* m_grid;
};