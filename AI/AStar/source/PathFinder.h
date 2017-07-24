#pragma once
#include "SFML\Graphics.hpp"

class Path;

class PathFinder
{
public:
    PathFinder();
    ~PathFinder();

    void Update();
private:
    // graphic
    sf::Texture* m_texture;
    sf::Sprite* m_sprite;

    // Path Finding
    Path* m_path;
};