#include "DrawCharacterSprite.h"
#include "Renderer.h"
#include "VectorMaths.h"
#include <algorithm>
#include "Agent.h"
#include "GameObject.h"

std::string getPath();

const sf::Vector2i pathFinderSpriteSize(40, 56);

DrawCharacterSprite::DrawCharacterSprite()
{
    m_texture.loadFromFile(getPath() + "\\resources\\graphics\\Character.png");
    m_sprite.setTexture(m_texture);

    m_sprite.setOrigin(sf::Vector2f(19, 46));
}

sf::Vector2f DrawCharacterSprite::update()
{
    updateSprite();
    Renderer::getInstance()->Draw(&m_sprite);

    return (sf::Vector2f(0, 0));
}

void DrawCharacterSprite::updateSprite()
{
    // turn based on velocity
    sf::Vector2f velocity = m_myAgent->getVelocity();

    if (distanceCheck(velocity, 0.0f))
    {
        m_movementState = MOVESTATE::IDLE;
    }
    else
    {
        if (distanceCheck(velocity, m_slowRadius))
        {
            m_movementState = MOVESTATE::WALK;
        }
        else
        {
            m_movementState = MOVESTATE::RUN;
        }

        float movementAngle = vectorAngle(velocity);

        if (movementAngle <= 22.5f || movementAngle > 337.5f)
        {
            m_movementDirection = MOVEDIRECTION::RIGHT;
        }
        else if (movementAngle <= 67.5f)
        {
            m_movementDirection = MOVEDIRECTION::DOWNRIGHT;
        }
        else if (movementAngle <= 112.5f)
        {
            m_movementDirection = MOVEDIRECTION::DOWN;
        }
        else if (movementAngle <= 157.5f)
        {
            m_movementDirection = MOVEDIRECTION::DOWNLEFT;
        }
        else if (movementAngle <= 202.5f)
        {
            m_movementDirection = MOVEDIRECTION::LEFT;
        }
        else if (movementAngle <= 247.5f)
        {
            m_movementDirection = MOVEDIRECTION::UPLEFT;
        }
        else if (movementAngle <= 292.5f)
        {
            m_movementDirection = MOVEDIRECTION::UP;
        }
        else if (movementAngle <= 337.5f)
        {
            m_movementDirection = MOVEDIRECTION::UPRIGHT;
        }
    }

    // animation
    if (m_clock.getElapsedTime().asSeconds() > (1.0f / (float)m_animationFrameRate))
    {
        currentSpriteCoordinate.x += pathFinderSpriteSize.x;
        if (currentSpriteCoordinate.x == (pathFinderSpriteSize.x * 6))
        {
            currentSpriteCoordinate.x = 0;
        }
        m_clock.restart();
    }

    // move to part of the sprite sheet based on movement state
    currentSpriteCoordinate.y = static_cast<int>(m_movementState) * (pathFinderSpriteSize.y * 5);
    currentSpriteCoordinate.y += (static_cast<int>(m_movementDirection) > 4 ? static_cast<int>(m_movementDirection) - 4 : static_cast<int>(m_movementDirection)) * pathFinderSpriteSize.y;

    if ((int)m_movementDirection < 5)
    {
        m_sprite.setScale(1, 1);
    }
    else
    {
        m_sprite.setScale(-1, 1);
    }
    m_sprite.setTextureRect(sf::IntRect(currentSpriteCoordinate, pathFinderSpriteSize));

    //m_sprite.setOrigin(sf::Vector2f(m_sprite.getGlobalBounds().width / 2.0f, m_sprite.getGlobalBounds().height / 2.0f));

    m_sprite.setPosition(m_myAgent->getPosition());
}
