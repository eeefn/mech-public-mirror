#include "../../headers/entities/EntityManager.h"
#include "../../headers/gameObjects/GameObjectManager.h"
#include "../../headers/controller/InputFactory.h"
#include "../../headers/controller/PlayInput.h"
#include "../../headers/Gui.h"
#include "../../headers/Camera.h"
#include "../../headers/Editor.h"
#include "../../headers/entities/AnimationCodes.h"
#include "../../headers/SoulColorCodes.h"
#include "../../headers/PlayerState.h"

using namespace SoulColors;

PlayInput playInput;
PlayInput::PlayInput(){

}

void PlayInput::processHeldKeys(SDL_Event *keyEvent){
	switch (keyEvent->key.keysym.sym){
		case SDLK_LSHIFT:
		
			entityManager.spawnSoulSprite();
			camera.setCameraTarget(entityManager.swapEntityList());
			inputFactory.setControlMode(controlModes.SOUL_SPRITE);
			if (camera.cameraTarget->hostEntity->velX > 0){
				camera.cameraTarget->velX += camera.cameraTarget->entitySpeedX;
			}
			else if(camera.cameraTarget->hostEntity->velX < 0){
				camera.cameraTarget->velX -= camera.cameraTarget->entitySpeedX;
			}
			camera.cameraTarget->hostEntity->stop();
			break;
	}
}

bool PlayInput::processInput(SDL_Event *keyEvent, int *gameMode){
	bool gameIsRunning = true;
	if (keyEvent->type == SDL_KEYDOWN && keyEvent->key.repeat == 0) {
		gameIsRunning = playInput.processKeydown(keyEvent, gameMode);
	}
	if (keyEvent->type == SDL_MOUSEBUTTONDOWN) {
		playInput.processMousedown(keyEvent);
		mousedown = true;
	}
	else if(keyEvent->type == SDL_MOUSEBUTTONUP){
		mousedown = false;
	}
	if(keyEvent->type == SDL_KEYDOWN && keyEvent->key.repeat != 0){
		playInput.processHeldKeys(keyEvent);
	}
	if (keyEvent->type == SDL_KEYUP && keyEvent->key.repeat == 0) {
		playInput.processKeyup(keyEvent);
	}
	else if (keyEvent->type == SDL_QUIT) {
			gameIsRunning = false;
	}
	return gameIsRunning;
}

void PlayInput::update(){
	if(mousedown){
		processHeldClick();		
	}
}

void PlayInput::processKeyup(SDL_Event *keyupEvent){
	Entity *playerEntity = camera.cameraTarget;
	switch (keyupEvent->key.keysym.sym) {
		case SDLK_a:
			playerEntity->moveLeft(false);
			break;
		case SDLK_d:
			playerEntity->moveRight(false);
			break;
		case SDLK_LSHIFT:
			camera.cameraTarget->requestAnimation(&PlayerAnimationCodes::MUSH_KNEEL,false);
	}
}

void PlayInput::processMousedown(SDL_Event *keydownEvent){
	if(playerState.inventoryOpen){
		playerState.handleInventoryClick(keydownEvent->button.x,keydownEvent->button.y,keydownEvent->button.button);
	}
	else{
		mousedown = true;
	}
}

void PlayInput::processHeldClick(){
	if(!playerState.inventoryOpen){
		if(camera.cameraTarget->facingL){
			camera.cameraTarget->requestAnimation(&PlayerAnimationCodes::TORSO_SWING_L,true);
		}
		else{
			camera.cameraTarget->requestAnimation(&PlayerAnimationCodes::TORSO_SWING_R,true);
		}
		int mouseXPos;
		int mouseYPos;
		auto buttonPressed = SDL_GetMouseState(&mouseXPos,&mouseYPos);
		GameObject *objectAtClick = gameObjectManager.getGameObjectAtClick(mouseXPos,mouseYPos,buttonPressed);
		if(objectAtClick != nullptr){
			Item *clickedBy = playerState.hotbar.getItemAtSelectedSlot();
			if(clickedBy != nullptr){
				objectAtClick->handleClick(clickedBy);
			}
		}
	}
}

int PlayInput::processKeydown(SDL_Event *keydownEvent, int *gameMode){
    bool gameIsRunning = true;
    Entity *playerEntity = camera.cameraTarget;
    switch (keydownEvent->key.keysym.sym) {
		case SDLK_UP:
			playerState.setSoulColor(RED);
			break;
		case SDLK_w:
			if (!playerEntity->inAir) {
				playerEntity->jump();
			}
			break;
		case SDLK_a:
			playerEntity->moveLeft(true);
			break;
		case SDLK_d:
			playerEntity->moveRight(true);
			break;
		case SDLK_e:
			*gameMode = 1; //something should be responsible for setting gamestate.
			//setup selector
			editor.setupSelector(playerEntity);
			break;
		case SDLK_q:
			{
			Entity* highlightedEntity = entityManager.getFirstHighlightedEntity();
			if(highlightedEntity != nullptr){
				int controlLockTime = MechAnimationCodes::POWER_UP.MAX_LOOP * MechAnimationCodes::POWER_UP.DEFAULT_SPEED;
				controlLockTime += MechAnimationCodes::STAND_UP.MAX_LOOP * MechAnimationCodes::STAND_UP.DEFAULT_SPEED;
				inputFactory.addLockTime(controlLockTime);
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
				highlightedEntity->hostEntity = playerEntity;
				playerEntity->inMech = true;
				highlightedEntity->isPlayer = true;
				highlightedEntity->highlighted = false;
				entityManager.changePlayerTarget(playerEntity,highlightedEntity,true);
				camera.cameraTarget->requestAnimation(&MechAnimationCodes::POWER_UP,true);
				camera.cameraTarget->requestAnimation(&MechAnimationCodes::POWER_UP_COLOR,true);
				inputFactory.setControlMode(controlModes.MECH);
			}else{
				GameObject* obj = gameObjectManager.getFirstHighlightedObject();
				if(obj != nullptr){
					obj->activate();
				}
			}
			}
			break;
		case SDLK_TAB:
			playerState.toggleInventory();
			break;
		case SDLK_LSHIFT:
			camera.cameraTarget->requestAnimation(&PlayerAnimationCodes::MUSH_KNEEL,true);
			break;
		case SDLK_1: playerState.hotbar.setSelectedSlot(0); break;
		case SDLK_2: playerState.hotbar.setSelectedSlot(1); break;
		case SDLK_3: playerState.hotbar.setSelectedSlot(2); break;
		case SDLK_4: playerState.hotbar.setSelectedSlot(3); break;
		case SDLK_5: playerState.hotbar.setSelectedSlot(4); break;
		case SDLK_6: playerState.hotbar.setSelectedSlot(5); break;
		case SDLK_7: playerState.hotbar.setSelectedSlot(6); break;
		case SDLK_8: playerState.hotbar.setSelectedSlot(7); break;
		case SDLK_9: playerState.hotbar.setSelectedSlot(8); break;
		case SDLK_0: playerState.hotbar.setSelectedSlot(9); break;
		case SDLK_ESCAPE: gameIsRunning = false; break;
	}
    return gameIsRunning;
}