#include "GameObject.h"
#include "Renderer.h"

std::string getPath();

// default constructor that doesn't set a sprite
GameObject::GameObject()
{
    m_texture = nullptr;
    m_sprite = nullptr;
    m_agent = new Agent(this);
}

// constructor that loads a sprite from a filename
GameObject::GameObject(std::string fileName)
{
    m_texture = nullptr;
    m_sprite = nullptr;
    setSprite(fileName);
    m_agent = new Agent(this);
}

// clean up in destructor
GameObject::~GameObject()
{
    delete m_sprite;
    delete m_texture;
    delete m_agent;
}

// loads a sprite from a png file and sets it as this GameObjects sprite
GameObject* GameObject::setSprite(std::string fileName)
{
    delete m_texture;
    m_texture = new sf::Texture;
    m_texture->loadFromFile(std::string(getPath() + "\\resources\\graphics\\" + fileName + ".png"));

    delete m_sprite;
    m_sprite = new sf::Sprite;
    m_sprite->setTexture(*m_texture);
    m_sprite->setOrigin((float)(m_texture->getSize().x / 2), (float)(m_texture->getSize().y / 2));

    return this;
}

// returns a pointer to our sprite
sf::Sprite* GameObject::getSprite()
{
    return m_sprite;
}

// returns a pointer to our Agent
Agent* GameObject::getAgent()
{
    return m_agent;
}

// updates this GameObject using its Agent
void GameObject::update()
{
    // only try to update the Agent if it exists
    if(m_agent)
    {
        m_agent->update();

        // only try to update the position of a sprite that exists
        if (m_sprite)
        {
            m_sprite->setPosition(m_agent->getPosition());
        }
    }
}

// draws this GameObject using the renderer
void GameObject::draw()
{
    // only try to draw the sprite if it is not nullptr
    if (m_sprite)
    {
        Renderer::getInstance()->Draw(m_sprite);
    }
}

// adds a new behavior to this GameObjects Agent
void GameObject::addBehavior(IBehavior* newBehavior, float newWeight)
{
    m_agent->addBehaviour(newBehavior, newWeight);
}

// pops a behaviour off the Agent
void GameObject::removeBehavior()
{
    m_agent->removeBehavior();
}
