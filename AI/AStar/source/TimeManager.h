#pragma once
#include <SFML\Graphics.hpp>

#define TIMEMANAGER TimeManager::getInstance()

// singleton
class TimeManager
{
public:
    static TimeManager* getInstance();

    float deltaTime();
    void update();
private:
    sf::Clock m_clock;
    float m_deltaTime;
};