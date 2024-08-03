#include "../../headers/controller/SoulSpriteInput.h"
#include "../../headers/entities/Entity.h"
#include "../../headers/entities/EntityManager.h"
#include "../../headers/controller/InputFactory.h"
#include "../../headers/Camera.h"
#include "../../headers/Map.h"
#include "../../headers/gameObjects/GameObjectManager.h"
#include "../../headers/gameObjects/GameObject.h"
#include "../../headers/constants.h"
#include "../../headers/entities/AnimationCodes.h"
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
	Entity *soulSpriteEntity = camera.cameraTarget;
	switch (keyupEvent->key.keysym.sym) {
		case SDLK_a:
            soulSpriteEntity->moveLeft(false);
			break;
		case SDLK_d:
        	soulSpriteEntity->moveRight(false);
			break;
        case SDLK_w:
            soulSpriteEntity->moveUp(false);
            break;
        case SDLK_s:
            soulSpriteEntity->moveDown(false);
            break;
		case SDLK_LSHIFT:
			entityManager.changePlayerTarget(soulSpriteEntity,soulSpriteEntity->hostEntity,false);
			entityManager.despawnEntity(soulSpriteEntity);
			inputFactory.setControlMode(controlModes.PLAYER);
			soulSpriteEntity->hostEntity->requestAnimation(&PlayerAnimationCodes::MUSH_KNEEL,false);
			break;
		case SDLK_q:
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
			{
			GameObject* highlightedObjectPtr = gameObjectManager.getFirstHighlightedObject();
			if(highlightedObjectPtr != nullptr){
				SDL_Event ev;
				ev.key.repeat = 0;
				ev.type = SDL_KEYDOWN;
				if(playerEntity->velX > 0){
					ev.key.keysym.sym = SDLK_d;
					SDL_PushEvent(&ev);
				}
				else if(playerEntity->velX < 0){
					ev.key.keysym.sym = SDLK_a;
					SDL_PushEvent(&ev);
				}
				int playerSpawnPosY = highlightedObjectPtr->yTile * mapInfo.TILE_DIM - 64/*this number is player height - size of object*/;
				int playerSpawnPosX = highlightedObjectPtr->xTile * mapInfo.TILE_DIM - 16/*this number is player width / 4*/;
				Entity* player = entityManager.spawnPlayer(playerSpawnPosX,playerSpawnPosY);
				player->requestAnimation(&PlayerAnimationCodes::MUSH_GROW,true);
				entityManager.changePlayerTarget(playerEntity,player,true);
				entityManager.despawnEntity(playerEntity);
				inputFactory.setControlMode(controlModes.PLAYER);
				gameObjectManager.removeObject(highlightedObjectPtr);
				inputFactory.addLockTime(PlayerAnimationCodes::MUSH_GROW.MAX_LOOP * PlayerAnimationCodes::MUSH_GROW.DEFAULT_SPEED);
			}
			}
            break;
		case SDLK_ESCAPE: gameIsRunning = false; break;
	}
    return gameIsRunning;
}