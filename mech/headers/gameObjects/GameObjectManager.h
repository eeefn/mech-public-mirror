#pragma once
#include "GameObject.h"
#include <SDL.h>
#include <vector>
#include <string>

class GameObjectManager{
    public:
        GameObjectManager();
        ~GameObjectManager();
        void manageHighlightedObjects(SDL_Rect* hitBox,const std::string& entityId);
        GameObject* getGameObjectAtClick(int xPos, int yPos,Uint32 clickType);
        void removeObject(GameObject* objToRemove);
        void queueObjectForRemoval(GameObject* objToRemove);
            void makeObject(short objectType,short xT, short yT);
        GameObject* makeUnmanagedObject(short objectType,short xT, short yT);
        void renderGameObjects(SDL_Renderer* rend);
        void updateGameObjects();
		GameObject* getFirstHighlightedObject();
        std::vector<GameObject*> gameObjectList;
    private:
        std::vector<GameObject*> objectsToRemove;
};

extern GameObjectManager gameObjectManager;