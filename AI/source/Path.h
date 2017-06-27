#pragma once
#include "PathNode.h"
#include <vector>

namespace sf
{
    class Font;
}

class Path
{
public:
    Path();
    ~Path();

    void addNode(sf::Vector2f position);
    PathNode* getNode(int index);
    void draw();
private:
    std::vector<PathNode*> m_pathNodes;
    sf::Font m_font;
    unsigned int nodeCount = 0;
};
