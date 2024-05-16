#include "../../headers/controller/PlayInput.h"
#include "../../headers/entities/Player.h"
#include "../../headers/entities/Mech.h"
#include "../../headers/Gui.h"


#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

PlayInput playInput;

PlayInput::PlayInput(){
    std::cout << "input constructed";
}

bool PlayInput::processInput(SDL_Event *keyEvent, vector<Entity*> *entityList, int *gameMode){
	bool gameIsRunning = true;
	if (keyEvent->type == SDL_KEYDOWN && keyEvent->key.repeat == 0) {
		gameIsRunning = playInput.processKeydown(keyEvent, entityList, gameMode);
	}
	if (keyEvent->type == SDL_MOUSEBUTTONDOWN) {
		playInput.processMousedown(keyEvent,entityList);
	}
	if (keyEvent->type == SDL_KEYUP && keyEvent->key.repeat == 0) {
		playInput.processKeyup(keyEvent, entityList);
	}
	else if (keyEvent->type == SDL_QUIT) {
			gameIsRunning = false;
	}
	return gameIsRunning;
}
void PlayInput::processKeyup(SDL_Event *keyupEvent, vector<Entity*> *entityList){
	Entity *playerEntity = entityList->at(0);
	switch (keyupEvent->key.keysym.sym) {
		case SDLK_a:
			playerEntity->moveLeft(false);
			break;
		case SDLK_d:
			playerEntity->moveRight(false);
			break;
	}
}

void PlayInput::processMousedown(SDL_Event *keydownEvent, vector<Entity*> *entityList){
	Entity *playerEntity = entityList->at(0);
	switch (keydownEvent->button.button) {
		case SDL_BUTTON_RIGHT:
			playerEntity->attackRight(keydownEvent->button.x);
			break;
	}
}

int PlayInput::processKeydown(SDL_Event *keydownEvent, vector<Entity*> *entityList, int *gameMode){
    bool gameIsRunning = true;
    Entity *playerEntity = entityList->at(0);
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
				mech.highlighted = false;
				//swap the position of mech and player.
				std::iter_swap(entityList->begin(), entityList->end() - 1);
				}
			break;
		case SDLK_ESCAPE: gameIsRunning = false; break;
	}
    return gameIsRunning;
}