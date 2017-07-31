#include "Edge.h"
#include "PathNode.h"
#include "Renderer.h"
#include "VectorMaths.h"

Edge::Edge(PathNode* newFirstNode, PathNode* newSecondNode)
{
    m_firstNode = newFirstNode;
    m_secondNode = newSecondNode;

    m_line.setFillColor(sf::Color(255, 255, 0));

    recalculate();
}

Edge::~Edge()
{

}

void Edge::setColor(sf::Color newColor)
{
    m_line.setFillColor(newColor);
}

void Edge::recalculate()
{
    sf::Vector2f centerOfNodes = (m_firstNode->getPosition() + m_secondNode->getPosition()) / 2.0f;
    float rotationAngle = angleBetweenVectors(m_firstNode->getPosition(), m_secondNode->getPosition());
    m_length = magnitude(m_secondNode->getPosition() - m_firstNode->getPosition());

    m_line.setSize(sf::Vector2f(m_length - 50.0f, 3));
    m_line.setOrigin(m_line.getLocalBounds().width / 2, m_line.getLocalBounds().height / 2);
    m_line.setPosition(centerOfNodes);
    m_line.setRotation(rotationAngle);
}

void Edge::draw()
{
    if (m_length > 50.0f)
    {
        Renderer::getInstance()->Draw(&m_line);
    }
}

