#pragma once
#include <SDL.h>
#include "./Entity.h"
#include <vector>
#include <algorithm>

using std::vector;

class EntityManager{
    public:
        EntityManager();
        void update(float dt);
        void render(int gameMode);
        Entity* swapEntityList(); 
        Entity* moveEntityToFront(Entity* entityToGoToFront);
        void despawnEntity(Entity* entityToDespawn);
        void spawnSoulSprite();
    private:
        vector<Entity*> entityList;
                        
};
extern EntityManager entityManager;