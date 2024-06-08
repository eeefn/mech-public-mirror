
#include "../../headers/entities/EntityManager.h"
#include "../../headers/entities/Player.h"
#include "../../headers/entities/Mech.h"
#include "../../headers/Map.h"
#include "../../headers/Collider.h"

EntityManager entityManager;

EntityManager::EntityManager(){
	Entity* pptr = &player;
	Entity* mptr = &mech;
	entityList.push_back(pptr);
	entityList.push_back(mptr);
}

void EntityManager::update(float dt){
	for(auto & entity : entityList){
		entity->updateEntity(dt);
	}
	for(auto & entity : entityList){
		if (collider.collisionCheck(entity, map.tileMap)) {
			entity->processCollision(collider.colResults);
		}
	}
}

void EntityManager::render(SDL_Renderer* renderer){
		//Iterate through the entity list, rendering every entity
		for(auto entity = entityList.rbegin(); entity != entityList.rend(); ++entity){
			(*entity)->render(renderer);
		}	
}

Entity* EntityManager::swapEntityList(){
	std::iter_swap(entityList.begin(), entityList.end() - 1);
	return entityList.at(0);
}