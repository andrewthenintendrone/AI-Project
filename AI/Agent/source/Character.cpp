#include "Character.h"
#include "Renderer.h"
#include "VectorMaths.h"
#include <algorithm>

std::string getPath();

const sf::Vector2i pathFinderSpriteSize(40, 56);

Character::Character()
{
    m_texture.loadFromFile(getPath() + "\\resources\\graphics\\Character.png");
    m_sprite.setTexture(m_texture);

    m_sprite.setOrigin(sf::Vector2f(m_sprite.getGlobalBounds().width / 2.0f, m_sprite.getGlobalBounds().height / 2.0f));

    m_font.loadFromFile(getPath() + "\\resources\\font\\calibri.ttf");
    m_text.setFont(m_font);
    m_text.setFillColor(sf::Color::White);
    m_text.setCharacterSize(40);
    m_text.setPosition(150, 150);
}

Character::~Character()
{

}

void Character::update()
{
    m_agent->update();
    m_sprite.setPosition(m_agent->getPosition());
    updateSprite();
}

void Character::draw()
{
    Renderer::getInstance()->Draw(&m_sprite);
    //Renderer::getInstance()->Draw(&m_text);
}

void Character::updateSprite()
{
    // turn based on velocity
    sf::Vector2f velocity = m_agent->getVelocity();

    if (magnitude(velocity) == 0.0f)
    {
        m_movementState = MOVESTATE::IDLE;
    }
    else
    {
        if (magnitude(velocity) < 200.0f)
        {
            m_movementState = MOVESTATE::WALK;
        }
        else
        {
            m_movementState = MOVESTATE::RUN;
        }

        float movementAngle = vectorAngle(velocity);
        m_text.setString("angle = " + std::to_string(movementAngle));

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
    currentSpriteCoordinate.y = (int)m_movementState * (pathFinderSpriteSize.y * 5);
    currentSpriteCoordinate.y += ((int)m_movementDirection > 4 ? (int)m_movementDirection - 4 : (int)m_movementDirection) * pathFinderSpriteSize.y;

    if ((int)m_movementDirection < 5)
    {
        m_sprite.setScale(1, 1);
    }
    else
    {
        m_sprite.setScale(-1, 1);
    }
    m_sprite.setTextureRect(sf::IntRect(currentSpriteCoordinate, pathFinderSpriteSize));

    m_sprite.setOrigin(sf::Vector2f(m_sprite.getGlobalBounds().width / 2.0f, m_sprite.getGlobalBounds().height / 2.0f));
}