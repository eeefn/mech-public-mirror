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
        void despawnEntity(Entity* entityToDespawn);
        void changePlayerTarget(Entity* fromEntity, Entity* toEntity);
        Entity* spawnSoulSprite();
        Entity* spawnPlayer(int xPos, int yPos);
        Entity* getFrontEntity();
        Entity* getFirstHighlightedEntity();
        Entity* moveEntityToFront(Entity* entityToGoToFront);
        Entity* swapEntityList(); 
    private:
        vector<Entity*> entityList;
                        
};
extern EntityManager entityManager;