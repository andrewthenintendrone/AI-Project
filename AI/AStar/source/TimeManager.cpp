#include "TimeManager.h"

// there is only ever one TimeManager
TimeManager* TimeManager::getInstance()
{
    static TimeManager instance;

    return &instance;
}

// returns current deltaTime
float TimeManager::deltaTime()
{
    return m_deltaTime;
}

// updates deltaTime
void TimeManager::update()
{
    m_deltaTime = m_clock.getElapsedTime().asSeconds();
    m_clock.restart();
}