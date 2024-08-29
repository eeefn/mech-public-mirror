#include "../../headers/gameObjects/GameObjectManager.h" 
#include "../../headers/gameObjects/GameObjectFactory.h"
#include "../../headers/Camera.h"
#include "../../headers/Collider.h"
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

//pass string into lambda factory function
//add returned object to list if it exists
void GameObjectManager::makeObject(short objectType, short xT, short yT){
	if(GameObject* pushBack = gameObjectFactory.makeObject(objectType,xT,yT)){
		gameObjectList.push_back(pushBack);
	}
}

void GameObjectManager::manageHighlightedObjects(SDL_Rect* hitBox,const std::string& entityId){
	for (auto gameObject : gameObjectList){
		if (collider.checkObjectCollision(hitBox, &gameObject->renObj)){
			if(gameObject->highlight(entityId)){
				break;
			};
		}
	}	
}
void GameObjectManager::renderGameObjects(SDL_Renderer* rend){
    for(auto gameObject : gameObjectList){
		gameObject->render(rend);
    }
}

void GameObjectManager::updateGameObjects(){
	for(auto gameObject : gameObjectList){
		gameObject->update();
	}
	manageHighlightedObjects(&camera.cameraTarget->displayRect,camera.cameraTarget->identifier);
}

GameObject* GameObjectManager::getFirstHighlightedObject(){
	for(auto gameObj : gameObjectList){
		if(gameObj->highlighted){
			return gameObj;
		}	
	}
	return nullptr;
}

GameObject* GameObjectManager::getGameObjectAtClick(int xPos, int yPos,Uint32 clickType){
	for(auto gameObject : gameObjectList){
		if(collider.pointWithinRect(xPos,yPos,gameObject->renObj)){
			return gameObject;
		}
	}
	return nullptr;
}

