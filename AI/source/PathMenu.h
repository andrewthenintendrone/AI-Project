#pragma once
#include "SFML\Graphics.hpp"
#include <vector>

class PathMenu
{
public:
    PathMenu();
    void draw();
private:
    std::vector<sf::Text> m_texts;
};