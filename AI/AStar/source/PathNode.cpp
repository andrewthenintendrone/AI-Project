#include "PathNode.h"
#include "Renderer.h"
#include "Edge.h"

PathNode::PathNode(sf::Vector2f newPosition)
{
    // node graphic
    m_graphic.setRadius(20.0f);
    m_graphic.setOutlineThickness(5.0f);

    m_graphic.setFillColor(sf::Color(128, 0, 255));
    m_graphic.setOutlineColor(sf::Color::Black);

    m_graphic.setOrigin(m_graphic.getLocalBounds().width / 2 - m_graphic.getOutlineThickness(), m_graphic.getGlobalBounds().height / 2 - m_graphic.getOutlineThickness());
    m_graphic.setPosition(newPosition);
}

PathNode::~PathNode()
{

}

void PathNode::addEdge(Edge* newEdge)
{
    m_edges.push_back(newEdge);
}

void PathNode::removeSingleEdge(Edge* edgeToRemove)
{
    m_edges.remove(edgeToRemove);
}

void PathNode::deleteEdges()
{
    for(std::list<Edge*>::iterator iter = m_edges.begin(); iter != m_edges.end();)
    {
        PathNode* otherNode = (this == (*iter)->m_firstNode ? (*iter)->m_secondNode : (*iter)->m_firstNode);
        otherNode->removeSingleEdge(*iter);
        delete (*iter);
        (*iter) = nullptr;
        iter = m_edges.erase(iter);
    }
}

void PathNode::draw()
{
    Renderer::getInstance()->Draw(&m_graphic);
    for (std::list<Edge*>::iterator iter = m_edges.begin(); iter != m_edges.end();)
    {
        if ((*iter) == nullptr)
        {
            iter = m_edges.erase(iter);
        }
        else
        {
            (*iter)->draw();
            iter++;
        }
    }
}

sf::CircleShape* PathNode::getGraphic()
{
    return &m_graphic;
}

sf::Vector2f PathNode::getPosition()
{
    return m_graphic.getPosition();
}

void PathNode::setPosition(sf::Vector2f newPosition)
{
    m_graphic.setPosition(newPosition);
    for (std::list<Edge*>::iterator iter = m_edges.begin(); iter != m_edges.end(); iter++)
    {
        (*iter)->recalculate();
    }
}

void PathNode::setColor(sf::Color newColor)
{
    m_graphic.setFillColor(newColor);
}

float PathNode::getGscore()
{
    return Gscore;
}

void PathNode::setGscore(float newGscore)
{
    Gscore = newGscore;
}

float PathNode::getHscore()
{
    return Hscore;
}

void PathNode::setHscore(float newHscore)
{
    Hscore = newHscore;
}

float PathNode::getFscore()
{
    return Fscore;
}

void PathNode::setFscore(float newFscore)
{
    Fscore = newFscore;
}

PathNode* PathNode::getPreviousNode()
{
    return m_prevNode;
}

void PathNode::setPreviousNode(PathNode* newPreviousNode)
{
    m_prevNode = newPreviousNode;
}

std::list<Edge*>* PathNode::getEdges()
{
    return &m_edges;
}

void PathNode::reset()
{
    Gscore = std::numeric_limits<float>::infinity();
    Hscore = std::numeric_limits<float>::infinity();
    Fscore = std::numeric_limits<float>::infinity();
    m_prevNode = nullptr;
}
