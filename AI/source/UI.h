#pragma once
#include <SFML\Graphics.hpp>
#include "Edge.h"
#include "PathNode.h"

class Path;

class UI
{
public:
    UI();

    void update(PathNode* selectedNode, bool clicking);
    void draw();
    void setPosition(sf::Vector2f newPosition);
    void setPath(Path* newPath);
    sf::FloatRect getBounds();
    bool isVisible = false;

private:
    // dropdown box graphic
    sf::RectangleShape m_dropDown;

    // create node option graphic
    sf::Texture m_optionCreateIcon;
    sf::Sprite m_optionCreateIconSprite;

    // destroy node option graphic
    sf::Texture m_optionDeleteIcon;
    sf::Sprite m_optionDeleteIconSprite;

    // link nodes option graphic
    sf::Texture m_optionLinkIcon;
    sf::Sprite m_optionLinkIconSprite;


    Path* m_path = nullptr;
    PathNode* selectedNode = nullptr;
};