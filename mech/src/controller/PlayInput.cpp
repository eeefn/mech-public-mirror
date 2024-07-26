#include "../../headers/controller/PlayInput.h"
#include "../../headers/entities/EntityManager.h"
#include "../../headers/Gui.h"
#include "../../headers/Camera.h"
#include "../../headers/Editor.h"
#include "../../headers/controller/InputFactory.h"
#include "../../headers/entities/AnimationCodes.h"
#include <iostream>

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
}

int PlayInput::processKeydown(SDL_Event *keydownEvent, int *gameMode){
    bool gameIsRunning = true;
    Entity *playerEntity = camera.cameraTarget;
    switch (keydownEvent->key.keysym.sym) {
		case SDLK_UP:
			gui.setSoulColor(gui.soulColors.RED);
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
			}
			}
			break;
		case SDLK_LSHIFT:
			camera.cameraTarget->requestAnimation(&PlayerAnimationCodes::MUSH_KNEEL,true);
			break;
		case SDLK_ESCAPE: gameIsRunning = false; break;
	}
    return gameIsRunning;
}