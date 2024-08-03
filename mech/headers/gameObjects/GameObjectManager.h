#pragma once
#include "GameObject.h"
#include <SDL.h>
#include <vector>
#include <unordered_map>
#include "Mushroom.h"
#include "Portal.h"

class GameObjectManager{
    public:
        GameObjectManager();
        ~GameObjectManager();
        using ObjectFactory = GameObject*(*)(int id, short xT, short yT);
        std::unordered_map<int,ObjectFactory> objectFactory = {
            {1, [](int id, short xT, short yT) -> GameObject* {Mushroom* mush = new Mushroom(0,id,xT,yT); return mush;}}, 
            {2, [](int id, short xT, short yT) -> GameObject* {Portal* port = new Portal();return port;}}
        };
        void manageHighlightedObjects(SDL_Rect* hitBox);
        void removeObject(GameObject* objToRemove);
        void makeObject(short objectType,short xT, short yT);
        void renderGameObjects(SDL_Renderer* rend);
		GameObject* getFirstHighlightedObject();
        std::vector<GameObject*> gameObjectList;
};

extern GameObjectManager gameObjectManager;