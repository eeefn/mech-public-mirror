#include "../../headers/controller/PlayInput.h"
#include "../../headers/entities/Player.h"
#include "../../headers/entities/Mech.h"
#include "../../headers/entities/EntityManager.h"
#include "../../headers/Gui.h"
#include "../../headers/Camera.h"


#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

PlayInput playInput;

PlayInput::PlayInput(){
    std::cout << "input constructed";
}

bool PlayInput::processInput(SDL_Event *keyEvent, int *gameMode){
	bool gameIsRunning = true;
	if (keyEvent->type == SDL_KEYDOWN && keyEvent->key.repeat == 0) {
		gameIsRunning = playInput.processKeydown(keyEvent, gameMode);
	}
	if (keyEvent->type == SDL_MOUSEBUTTONDOWN) {
		playInput.processMousedown(keyEvent);
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
			if(!playerEntity->entityTransition){
				playerEntity->moveLeft(false);
			}else{
				playerEntity->entityTransition = false;
			}
			break;
		case SDLK_d:
			if(!playerEntity->entityTransition){
				playerEntity->moveRight(false);
			}else{
				playerEntity->entityTransition = false;
			}
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
			gui.soulColor = gui.soulColor++;
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
			*gameMode = 1;
			//setup selector
			gui.selWindowRen.h = TILE_DIM;
			gui.selWindowRen.w = TILE_DIM;
			gui.selWindowRen.x = (playerEntity->displayRect.x % TILE_DIM);
			gui.selWindowRen.y = /*selOffY - */(playerEntity->displayRect.y % TILE_DIM);
			break;
		case SDLK_q:
			if (mech.highlighted) {
				mech.isPlayer = true;
				player.isPlayer = false;
				player.inMech = true;
				mech.highlighted = false;
				mech.entityTransition = true;
				//player.stop();
				//swap the position of mech and player.
				
				camera.setCameraTarget(entityManager.swapEntityList());
			}
			break;
		case SDLK_ESCAPE: gameIsRunning = false; break;
	}
    return gameIsRunning;
}