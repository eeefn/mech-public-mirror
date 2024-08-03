#include "../../headers/gameObjects/GameObjectManager.h" 
#include "../../headers/Collider.h"
#include <iostream>
#include <algorithm>
GameObjectManager gameObjectManager;

GameObjectManager::GameObjectManager(){

}
GameObjectManager::~GameObjectManager(){
	for(auto gameObj : gameObjectList){
		delete gameObj;
	}
	gameObjectList.clear();
}

void GameObjectManager::removeObject(GameObject* objToRemove){
	auto objIterator = find(gameObjectList.begin(),gameObjectList.end(),objToRemove);
	if(objIterator != gameObjectList.end()){
		gameObjectList.erase(objIterator);	
	}
	delete objToRemove;	
}

void GameObjectManager::makeObject(short objectType, short xT, short yT){
    auto objIt = objectFactory.find(objectType);
    if(objIt != objectFactory.end()){
        gameObjectList.push_back(objIt->second(objectType,xT,yT));
    }
    //pass string into lambda factory function
    //add returned object to list
}

void GameObjectManager::manageHighlightedObjects(SDL_Rect* hitBox){
	for (auto gameObject : gameObjectList){
		if (collider.checkObjectCollision(hitBox, &gameObject->renObj)){
			gameObject->highlight(true);
		}else{
			gameObject->highlight(false);
		}
	}	
}
void GameObjectManager::renderGameObjects(SDL_Renderer* rend){
    for(auto gameObject : gameObjectList){

    }
}

GameObject* GameObjectManager::getFirstHighlightedObject(){
	for(auto gameObj : gameObjectList){
		if(gameObj->highlighted){
			return gameObj;
		}	
	}
	return nullptr;
}