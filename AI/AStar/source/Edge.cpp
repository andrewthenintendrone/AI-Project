#include "Edge.h"
#include "PathNode.h"
#include "Renderer.h"
#include "VectorMaths.h"

Edge::Edge(PathNode* newFirstNode, PathNode* newSecondNode)
{
    m_firstNode = newFirstNode;
    m_secondNode = newSecondNode;

    m_line.setFillColor(sf::Color::Magenta);

    recalculate();
}

Edge::~Edge()
{

}

void Edge::recalculate()
{
    sf::Vector2f centerOfNodes = (m_firstNode->getPosition() + m_secondNode->getPosition()) / 2.0f;
    float rotationAngle = angleBetweenVectors(m_firstNode->getPosition(), m_secondNode->getPosition());
    float lineLength = magnitude(m_secondNode->getPosition() - m_firstNode->getPosition());

    m_line.setSize(sf::Vector2f(lineLength, 3));
    m_line.setOrigin(m_line.getLocalBounds().width / 2, m_line.getLocalBounds().height / 2);
    m_line.setPosition(centerOfNodes);
    m_line.setRotation(rotationAngle);
}

void Edge::draw()
{
    Renderer::getInstance()->Draw(&m_line);
}
