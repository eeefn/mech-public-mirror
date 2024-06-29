#include "../../headers/controller/PlayInput.h"
#include "../../headers/entities/Player.h"
#include "../../headers/entities/Mech.h"
#include "../../headers/entities/EntityManager.h"
#include "../../headers/Gui.h"
#include "../../headers/Camera.h"
#include "../../headers/Editor.h"
#include "../../headers/controller/InputFactory.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

PlayInput playInput;

PlayInput::PlayInput(){
    std::cout << "input constructed";
}

void PlayInput::processHeldKeys(SDL_Event *keyEvent){
	switch (keyEvent->key.keysym.sym){
		case SDLK_LSHIFT:
			//if(!soulSpriteSpawned){
			entityManager.spawnSoulSprite();
			camera.setCameraTarget(entityManager.swapEntityList());
			soulSpriteSpawned = true;
			inputFactory.setControlMode(controlModes.SOUL_SPRITE);
		//	}
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
			//TODO despawn soulSprite entity
			//TODO switch camera back to player entity
			break;
	}
}

void PlayInput::processMousedown(SDL_Event *keydownEvent){
	Entity *playerEntity = camera.cameraTarget;
	switch (keydownEvent->button.button) {
		case SDL_BUTTON_RIGHT:
			playerEntity->attackRight(keydownEvent->button.x);
			break;
	}
}

int PlayInput::processKeydown(SDL_Event *keydownEvent, int *gameMode){
    bool gameIsRunning = true;
    Entity *playerEntity = camera.cameraTarget;
    switch (keydownEvent->key.keysym.sym) {
		case SDLK_DOWN:
			player.soul = player.soul - 5;
			break;
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
			if (mech.highlighted) {
				mech.isPlayer = true;
				player.isPlayer = false;
				player.inMech = true;
				mech.highlighted = false;
				if(player.velX > 0){
					mech.velX += mech.entitySpeedX;
				}
				else if(player.velX < 0){
					mech.velX -= mech.entitySpeedX;
				}
				camera.setCameraTarget(entityManager.swapEntityList());
			}
			break;
		case SDLK_ESCAPE: gameIsRunning = false; break;
	}
    return gameIsRunning;
}