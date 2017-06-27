#include "Path.h"
#include "SFML\Graphics.hpp"

std::string getPath();

Path::Path()
{
    m_font.loadFromFile(getPath() + "\\resources\\font\\comic.ttf");
}

Path::~Path()
{
    for each (PathNode* currentNode in m_pathNodes)
    {
        delete currentNode;
    }
}

void Path::addNode(sf::Vector2f position)
{
    m_pathNodes.push_back(new PathNode(position, &m_font, nodeCount));
    nodeCount++;
}

PathNode* Path::getNode(int index)
{
    return m_pathNodes[index];
}

void Path::draw()
{
    for each (PathNode* currentNode in m_pathNodes)
    {
        currentNode->draw();
    }
}