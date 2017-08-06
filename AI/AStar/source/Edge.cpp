#include "Edge.h"
#include "PathNode.h"
#include "Renderer.h"
#include "VectorMaths.h"

// constructor takes two already existing path nodes
Edge::Edge(PathNode* newFirstNode, PathNode* newSecondNode)
{
    // store node pointers
    m_firstNode = newFirstNode;
    m_secondNode = newSecondNode;

    // color line yellow by default
    m_line.setFillColor(YELLOW());

    // recalculate once for first draw
    recalculate();
}

Edge::~Edge()
{

}

// sets the color of the edge
void Edge::setColor(sf::Color newColor)
{
    m_line.setFillColor(newColor);
}

// recalculates how the line graphic should look
void Edge::recalculate()
{
    // find the center of the nodes
    sf::Vector2f centerOfNodes = (m_firstNode->getPosition() + m_secondNode->getPosition()) / 2.0f;

    // find the angle between the nodes
    float rotationAngle = angleBetweenVectors(m_firstNode->getPosition(), m_secondNode->getPosition());

    // find the distance between the nodes
    m_length = magnitude(m_secondNode->getPosition() - m_firstNode->getPosition());

    // set the line graphics length to the distance between the nodes (subtract 50 to not overlap the outline)
    m_line.setSize(sf::Vector2f(m_length - 50.0f, 3));

    // set the line graphics origin to its new center
    m_line.setOrigin(m_line.getLocalBounds().width / 2, m_line.getLocalBounds().height / 2);

    // set the line graphics position to the center of the nodes
    m_line.setPosition(centerOfNodes);

    // set the line graphics rotation to the angle between the nodes
    m_line.setRotation(rotationAngle);
}

// draws the edge
void Edge::draw()
{
    // don't draw if the length is less than 50 to avoid negative lengths
    if (m_length > 50.0f)
    {
        Renderer::getInstance()->Draw(&m_line);
    }
}

