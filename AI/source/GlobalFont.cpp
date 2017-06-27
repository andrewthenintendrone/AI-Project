#include "GlobalFont.h"
std::string getPath();

sf::Font GlobalFont::getInstance()
{
    static sf::Font g_font;
    g_font.loadFromFile(getPath() + "\\resources\\font\\comic.ttf");
    return g_font;
}