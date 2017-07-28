#include "ObjectPool.h"
#include "Renderer.h"

ObjectPool* ObjectPool::getInstance()
{
    static ObjectPool instance;
    return &instance;
}

ObjectPool::~ObjectPool()
{
    //m_objectPool.empty();
}

GameObject* ObjectPool::createObject(std::string key)
{
    GameObject* newGameObject = new GameObject;
    m_objectPool.insert(std::pair<std::string, GameObject*>(key, newGameObject));
    return newGameObject;
}

GameObject* ObjectPool::getObject(std::string key)
{
    return m_objectPool.at(key);
}

void ObjectPool::updateAllObjects()
{
    for (std::map<std::string, GameObject*>::iterator iter = m_objectPool.begin(); iter != m_objectPool.end(); iter++)
    {
        if (iter->second)
        {
            iter->second->update();
        }
    }
}

void ObjectPool::drawAllObjects()
{
    for (std::map<std::string, GameObject*>::iterator iter = m_objectPool.begin(); iter != m_objectPool.end(); iter++)
    {
        if (iter->second)
        {
            iter->second->draw();
        }
    }
}

// creates a vector from the pool and returns it
std::vector<GameObject*> ObjectPool::getPool()
{
    std::vector<GameObject*> pool;
    for (auto iter = m_objectPool.begin(); iter != m_objectPool.end(); iter++)
    {
        if (iter->second)
        {
            pool.push_back(iter->second);
        }
    }
    return pool;
}