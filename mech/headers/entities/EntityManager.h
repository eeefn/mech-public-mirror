#pragma once
#include <SDL.h>
#include "./Entity.h"
#include <vector>

using std::vector;

class EntityManager{
    public:
        EntityManager();
        void update(float dt);
        void render(int gameMode);
        Entity* swapEntityList(); 
    private:
        vector<Entity*> entityList;
                        
};
extern EntityManager entityManager;