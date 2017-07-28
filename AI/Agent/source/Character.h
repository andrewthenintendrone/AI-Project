#pragma once
#include "GameObject.h"
#include "SFML\Graphics.hpp"
#include <list>

enum class MOVESTATE { IDLE, WALK, RUN };
enum class MOVEDIRECTION { DOWN, LEFT, DOWNLEFT, UPLEFT, UP, RIGHT, DOWNRIGHT, UPRIGHT };

class Character : public GameObject
{
public:
    Character();
    ~Character();

    void update();
    void draw();

private:
    // graphics
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    MOVESTATE m_movementState = MOVESTATE::RUN;
    MOVEDIRECTION m_movementDirection = MOVEDIRECTION::DOWNRIGHT;
    sf::Vector2i currentSpriteCoordinate;
    int m_animationFrameRate = 10;
    sf::Clock m_clock;

    void updateSprite();
    sf::Font m_font;
    sf::Text m_text;
};