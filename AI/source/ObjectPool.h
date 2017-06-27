#pragma once
#include <vector>
#include "GameObject.h"
#include <map>
#include <vector>

class ObjectPool
{
public:
    static ObjectPool* getInstance();
    ~ObjectPool();
    GameObject* createObject(std::string key);
    GameObject* getObject(std::string key);
    void updateAllObjects();
    void drawAllObjects();

    std::vector<GameObject*> getPool();
private:
    std::map<std::string, GameObject*> m_objectPool;
};