#pragma once
#include "IBehavior.h"

enum class MOVESTATE { IDLE, WALK, RUN };
enum class MOVEDIRECTION { DOWN, LEFT, DOWNLEFT, UPLEFT, UP, RIGHT, DOWNRIGHT, UPRIGHT };

class DrawCharacterSprite : public IBehavior
{

public:

    DrawCharacterSprite();

    sf::Vector2f update();

private:

    // graphics
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    MOVESTATE m_movementState = MOVESTATE::RUN;
    MOVEDIRECTION m_movementDirection = MOVEDIRECTION::DOWNRIGHT;
    sf::Vector2i currentSpriteCoordinate;
    int m_animationFrameRate = 10;
    sf::Clock m_clock;
    float m_slowRadius = 200.0f;

    void updateSprite();
};