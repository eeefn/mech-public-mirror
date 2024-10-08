#include "../../headers/gameObjects/GameObjectManager.h" 
#include "../../headers/gameObjects/GameObjectFactory.h"
#include "../../headers/gameObjects/GardenBoxObject.h"
#include "../../headers/Camera.h"
#include "../../headers/Collider.h"
#include <algorithm>
#include <iostream>

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

GameObject* GameObjectManager::makeUnmanagedObject(short objectType,short xT, short yT){
	GameObject* unmanagedObj = gameObjectFactory.makeObject(objectType, xT,yT);
	return unmanagedObj;
}
//pass string into lambda factory function
//add returned object to list if it exists
void GameObjectManager::makeObject(short objectType, short xT, short yT){
	if(GameObject* pushBack = gameObjectFactory.makeObject(objectType,xT,yT)){
		gameObjectList.push_back(pushBack);
	}
}

bool GameObjectManager::checkObjectObjectListCollision(GameObject* obj){
	for(auto objInList : gameObjectList){
		if(collider.checkRectRectCollision(&obj->renderRects.posOnScreen,&objInList->renderRects.posOnScreen)){
			return true;
		}
	}
	return false;	
}

void GameObjectManager::manageHighlightedObjects(SDL_Rect* hitBox,const std::string& entityId){
	for (auto gameObject : gameObjectList){
		if (collider.checkRectRectCollision(hitBox, &gameObject->renderRects.posOnScreen)){
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
	for(auto remObject : objectsToRemove){
		removeObject(remObject);
	}
	objectsToRemove.clear();
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

bool GameObjectManager::returnManagedObject(GameObject* objReturned){
	if(objReturned != nullptr){
		gameObjectList.push_back(objReturned);
		return true;
	}
	return false;
}
GameObject* GameObjectManager::getGameObjectAtClick(int xPos, int yPos,Uint32 clickType){
	for(auto gameObject : gameObjectList){
		if(collider.checkPointWithinRect(xPos,yPos,gameObject->renderRects.posOnScreen)){
			return gameObject;
		}
	}
	return nullptr;
}
//allows objects to request their own deletion on the next update cycle
void GameObjectManager::queueObjectForRemoval(GameObject* objToRemove){
	objectsToRemove.push_back(objToRemove);
}

const bool GameObjectManager::checkForLeftNeighbor(GameObject* obj){
	SDL_Rect leftShiftedRect = obj->renderRects.posOnScreen;
	leftShiftedRect.x = leftShiftedRect.x - leftShiftedRect.w;
	for(auto objInList : gameObjectList){
		if(objInList->ID == obj->ID){
			if(objInList->renderRects.posOnScreen.x == leftShiftedRect.x){
				GardenBoxObject* cast = dynamic_cast<GardenBoxObject*>(objInList);
				cast->updateRenderTextureL();
				return true;
			}
		}
	}
	return false;
}

const bool GameObjectManager::checkForRightNeighbor(GameObject* obj){
	SDL_Rect rightShiftedRect = obj->renderRects.posOnScreen;
	rightShiftedRect.x = rightShiftedRect.x + rightShiftedRect.w;
	for(auto objInList : gameObjectList){
		if(objInList->ID == obj->ID){
			if(objInList->renderRects.posOnScreen.x == rightShiftedRect.x){
				GardenBoxObject* cast = dynamic_cast<GardenBoxObject*>(objInList);
				cast->updateRenderTextureR();
				return true;
			}			
		}
	}
	return false;
}