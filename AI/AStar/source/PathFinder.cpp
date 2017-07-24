#include "PathFinder.h"
#include "Renderer.h"

std::string getPath();

PathFinder::PathFinder()
{
    m_texture = new sf::Texture;
    m_texture->loadFromFile(getPath() + "\\resources\\graphics\\PathFinder.png");
    m_sprite = new sf::Sprite;
    m_sprite->setTexture(*m_texture);
}

PathFinder::~PathFinder()
{
    delete m_sprite;
    delete m_texture;
}

void PathFinder::Update()
{
    Renderer::getInstance()->Draw(m_sprite);
}