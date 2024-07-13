#include "../../headers/controller/SoulSpriteInput.h"
#include "../../headers/entities/Entity.h"
#include "../../headers/entities/EntityManager.h"
#include "../../headers/controller/InputFactory.h"
#include "../../headers/Camera.h"
#include "../../headers/Map.h"
#include "../../headers/GameObject.h"
#include "../../headers/constants.h"
SoulSpriteInput soulSpriteInput;

SoulSpriteInput::SoulSpriteInput(){
    return;
}

bool SoulSpriteInput::processInput(SDL_Event *keyEvent, int *gameMode){
	bool gameIsRunning = true;
	if (keyEvent->type == SDL_KEYDOWN && keyEvent->key.repeat == 0) {
		gameIsRunning = soulSpriteInput.processKeydown(keyEvent, gameMode);
	}
	if (keyEvent->type == SDL_KEYUP && keyEvent->key.repeat == 0) {
		soulSpriteInput.processKeyup(keyEvent);
	}
	else if (keyEvent->type == SDL_QUIT) {
			gameIsRunning = false;
	}
	return gameIsRunning;
}

void SoulSpriteInput::processKeyup(SDL_Event *keyupEvent){
	Entity *playerEntity = camera.cameraTarget;
	switch (keyupEvent->key.keysym.sym) {
		case SDLK_a:
            playerEntity->moveLeft(false);
			break;
		case SDLK_d:
            playerEntity->moveRight(false);
			break;
        case SDLK_w:
            playerEntity->moveUp(false);
            break;
        case SDLK_s:
            playerEntity->moveDown(false);
            break;
		case SDLK_LSHIFT:
			if(playerEntity->velX > 0){
				playerEntity->hostEntity->velX += playerEntity->hostEntity->entitySpeedX;
			}
			else if(playerEntity->velX < 0){
				playerEntity->hostEntity->velX -= playerEntity->hostEntity->entitySpeedX;
			}
		 	entityManager.moveEntityToFront(playerEntity->hostEntity);
			camera.setCameraTarget(playerEntity->hostEntity);
			entityManager.despawnEntity(playerEntity);
			inputFactory.setControlMode(controlModes.PLAYER);
			break;
		case SDLK_q:
			GameObject* highlightedObjectPtr = map.getFirstHighlightedObject();
			int playerSpawnPosX = highlightedObjectPtr->xTile * mapInfo.TILE_DIM - 16/*this number is player width / 4*/;
			int playerSpawnPosY = highlightedObjectPtr->yTile * mapInfo.TILE_DIM - 64/*this number is player height - size of object*/;
			if(highlightedObjectPtr != nullptr){
				Entity* player = entityManager.spawnPlayer(playerSpawnPosX,playerSpawnPosY);
				player->requestAnimation(playerEntity);
				entityManager.despawnEntity(playerEntity);
				entityManager.moveEntityToFront(player);
				camera.setCameraTarget(player);
				inputFactory.setControlMode(controlModes.PLAYER);
			}
		 //initiate transition
			break;
	}
}

int SoulSpriteInput::processKeydown(SDL_Event *keydownEvent, int *gameMode){
    bool gameIsRunning = true;
    Entity *playerEntity = camera.cameraTarget;
    switch (keydownEvent->key.keysym.sym) {
		case SDLK_w:
            playerEntity->moveUp(true);
			break;
		case SDLK_a:
			playerEntity->moveLeft(true);
			break;
		case SDLK_d:
			playerEntity->moveRight(true);
			break;
        case SDLK_s:
            playerEntity->moveDown(true);
            break;
        case SDLK_q:
            //this is where the player would switch entites
            break;
		case SDLK_ESCAPE: gameIsRunning = false; break;
	}
    return gameIsRunning;
}