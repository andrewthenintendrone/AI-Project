#include "GameObject.h"
#include "Renderer.h"
std::string getPath();

GameObject::GameObject()
{
    m_texture = nullptr;
    m_sprite = nullptr;
    m_text = nullptr;
    m_agent = new Agent(this);
}

GameObject::GameObject(std::string fileName)
{
    m_texture = nullptr;
    m_sprite = nullptr;
    m_text = nullptr;
    setSprite(fileName);
    m_agent = new Agent(this);
}

GameObject::~GameObject()
{
    delete m_sprite;
    delete m_texture;
    delete m_text;
    delete m_agent;
}

GameObject* GameObject::setSprite(std::string fileName)
{
    delete m_texture;
    m_texture = new sf::Texture;
    m_texture->loadFromFile(getPath() + "\\resources\\graphics\\" + fileName + ".png");
    m_sprite->setTexture(*m_texture);
    m_sprite->setOrigin((float)(m_texture->getSize().x / 2), (float)(m_texture->getSize().y / 2));
    return this;
}

sf::Sprite* GameObject::getSprite()
{
    return m_sprite;
}

GameObject* GameObject::setText(std::string& newText, sf::Font& newFont)
{
    delete m_text;
    m_text = new sf::Text;
    m_text->setString(newText);
    m_text->setFillColor(sf::Color::White);
    m_text->setFont(newFont);
    m_text->setOrigin((float)(m_text->getGlobalBounds().width / 2), (float)(m_text->getGlobalBounds().height / 2));
    return this;
}

sf::Text* GameObject::getText()
{
    return m_text;
}

Agent* GameObject::getAgent()
{
    return m_agent;
}

// updates this GameObject using its Agent
void GameObject::Update()
{
    if(m_agent)
    {
        m_agent->Update();
        if (m_sprite)
        {
            m_sprite->setPosition(m_agent->getPosition());
            m_sprite->setRotation(m_agent->getRotation());
        }
        if (m_text)
        {
            m_text->setPosition(m_agent->getPosition());
            m_text->setRotation(m_agent->getRotation());
        }
    }
}

// draws this GameObject using the renderer
void GameObject::Draw()
{
    if (m_sprite)
    {
        Renderer::getInstance()->Draw(m_sprite);
    }
    if (m_text)
    {
        Renderer::getInstance()->Draw(m_text);
    }
}

// sets a 
void GameObject::addBehavior(IBehavior* newBehavior)
{
    m_agent->addBehaviour(newBehavior);
}