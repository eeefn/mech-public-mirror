#pragma once
#include "GameObject.h"
#include <SDL.h>
#include <vector>
#include <unordered_map>
#include "Mushroom.h"
#include "Portal.h"
#include "RockObject.h"
#include "ShrubObject.h"
#include "GameObjectCodes.h"

using namespace gameObjectCodes;
class GameObjectManager{
    public:
        GameObjectManager();
        ~GameObjectManager();
        using ObjectFactory = GameObject*(*)(int id, short xT, short yT);
        std::unordered_map<int,ObjectFactory> objectFactory = {
            {MUSHROOM, [](int id, short xT, short yT) -> GameObject* {Mushroom* mush = new Mushroom(0,id,xT,yT); return mush;}}, 
            {PORTAL, [](int id, short xT, short yT) -> GameObject* {Portal* port = new Portal(id,xT,yT);return port;}},
            {ROCK_0, [](int id, short xT, short yT) -> GameObject* {RockObject* rock0 = new RockObject(id,xT,yT,0);return rock0;}},
            {ROCK_1, [](int id, short xT, short yT) -> GameObject* {RockObject* rock1 = new RockObject(id,xT,yT,1);return rock1;}},
            {ROCK_2, [](int id, short xT, short yT) -> GameObject* {RockObject* rock2 = new RockObject(id,xT,yT,2);return rock2;}},
            {SHRUB_0, [](int id, short xT, short yT) -> GameObject* {GameObject* shrub0 = new ShrubObject(id,xT,yT,0);return shrub0;}},
            {SHRUB_1, [](int id, short xT, short yT) -> GameObject* {GameObject* shrub1 = new ShrubObject(id,xT,yT,1);return shrub1;}},
            {SHRUB_2, [](int id, short xT, short yT) -> GameObject* {ShrubObject* shrub2 = new ShrubObject(id,xT,yT,2);return shrub2;}}
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