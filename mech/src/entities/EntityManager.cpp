
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
	Entity* pptr = new Player();
	Entity* mptr = &mech;
	entityList.push_back(pptr);
	entityList.push_back(mptr);
}

Entity* EntityManager::getFrontEntity(){
	return entityList.at(0);
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
	if(gameMode == gamemodes.PLAY){
		for(auto entity = entityList.rbegin(); entity != entityList.rend(); ++entity){
			(*entity)->render(windowManager.renderer);
		}	
	}
}
void EntityManager::spawnSoulSprite(){
	Entity* soulSprite = new SoulSprite(entityList.at(0));
	entityList.push_back(soulSprite);
}

void EntityManager::spawnPlayer(int xPos, int yPos){
	Entity* player = new Player();
	player->posX = xPos;
	player->posY = yPos;
	entityList.push_back(player);
}
Entity* EntityManager::swapEntityList(){
	std::iter_swap(entityList.begin(), entityList.end() - 1);
	std::cout << "swapped entity list" << std::endl;
	std::cout << entityList.size() << std::endl;
	return entityList.at(0);
}

Entity* EntityManager::moveEntityToFront(Entity* entityToGoToFront){
	auto toSwapIterator = std::find(entityList.begin(),entityList.end(),entityToGoToFront);
	if(toSwapIterator != entityList.end()){
		std::iter_swap(entityList.begin(),toSwapIterator);
	}
	return entityList.at(0);
}
 
void EntityManager::despawnEntity(Entity* entityToDespawn){
	auto entity = std::find(entityList.begin(),entityList.end(),entityToDespawn);
	if(entity != entityList.end()){
		entityList.erase(entity);
	}
	else{
		std::cout << "entity to erase does not exist" << std::endl;
	}
	delete entityToDespawn;
}
