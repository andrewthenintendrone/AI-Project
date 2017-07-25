#include "Path2.h"
#include "InputManager.h"
#include "Renderer.h"

Path2::Path2()
{

}

Path2::~Path2()
{

}

void Path2::update()
{
    m_ui.update();

    if (m_ui.getUImode() == UIMODE::ADDING)
    {
        if (InputManager::getInstance()->getLeftClick() && InputManager::getInstance()->getMousePosf().x < Renderer::getInstance()->getWindowSizef().x - 200.0f)
        {
            addNode(InputManager::getInstance()->getMousePosf());
        }
    }
}

void Path2::draw()
{
    for (std::list<PathNode2*>::iterator iter = m_PathNodes.begin(); iter != m_PathNodes.end(); iter++)
    {
        (*iter)->draw();
    }
    m_ui.draw();
}

void Path2::addNode(sf::Vector2f position)
{
    m_PathNodes.push_back(new PathNode2(position));
}

void Path2::removeNode(PathNode2* nodeToRemove)
{
    m_PathNodes.remove(nodeToRemove);
}
