
#include "../../headers/entities/EntityManager.h"
#include "../../headers/entities/Player.h"
#include "../../headers/entities/Mech.h"
#include "../../headers/entities/SoulSprite.h"
#include "../../headers/WindowManager.h"
#include "../../headers/Map.h"
#include "../../headers/Collider.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
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

void EntityManager::render(int gameMode){
	//Iterate through the entity list, rendering every entity
	//Iteration is done in reverse to ensure that the player is rendered in front of other entities
	if(gameMode == PLAY){
		for(auto entity = entityList.rbegin(); entity != entityList.rend(); ++entity){
			(*entity)->render(windowManager.renderer);
		}	
	}
}
void EntityManager::spawnSoulSprite(){
	Entity* soulSprite = new SoulSprite(entityList.at(0));
	entityList.push_back(soulSprite);
}
Entity* EntityManager::swapEntityList(){
	std::iter_swap(entityList.begin(), entityList.end() - 1);
	std::cout << "swapped entity list" << std::endl;
	std::cout << entityList.size() << std::endl;
	return entityList.at(0);
}