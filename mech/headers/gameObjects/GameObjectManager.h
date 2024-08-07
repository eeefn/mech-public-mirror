#pragma once
#include "GameObject.h"
#include <SDL.h>
#include <vector>
#include <unordered_map>
#include "Mushroom.h"
#include "Portal.h"
#include "Rock.h"

class GameObjectManager{
    public:
        GameObjectManager();
        ~GameObjectManager();
        using ObjectFactory = GameObject*(*)(int id, short xT, short yT);
        std::unordered_map<int,ObjectFactory> objectFactory = {
            {1, [](int id, short xT, short yT) -> GameObject* {Mushroom* mush = new Mushroom(0,id,xT,yT); return mush;}}, 
            {2, [](int id, short xT, short yT) -> GameObject* {Portal* port = new Portal(id,xT,yT);return port;}},
            {3, [](int id, short xT, short yT) -> GameObject* {Rock* rock0 = new Rock(id,xT,yT,0);return rock0;}},
            {4, [](int id, short xT, short yT) -> GameObject* {Rock* rock1 = new Rock(id,xT,yT,1);return rock1;}},
            {5, [](int id, short xT, short yT) -> GameObject* {Rock* rock2 = new Rock(id,xT,yT,2);return rock2;}}
        };
        void manageHighlightedObjects(SDL_Rect* hitBox,const string& entityId);
        void removeObject(GameObject* objToRemove);
        void makeObject(short objectType,short xT, short yT);
        void renderGameObjects(SDL_Renderer* rend);
        void updateGameObjects();
		GameObject* getFirstHighlightedObject();
        std::vector<GameObject*> gameObjectList;
};

extern GameObjectManager gameObjectManager;