#pragma once
#include <vector>
#include "GameObject.h"
class GameObjectManager{
    public:
        GameObjectManager();
        std::vector<GameObject*> gameObjectList;
};

extern GameObjectManager gameObjectManager;