#include "../headers/PlayInput.h"
#include "../headers/Player.h"
#include "../headers/Gui.h"
#include "../headers/Mech.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

PlayInput input;

PlayInput::PlayInput(){
    std::cout << "input constructed";
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

int PlayInput::processKeydown(SDL_Event *keydownEvent, vector<Entity*> *entityList){
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
		/*case SDLK_e:
			gameMode = 1;
			//setup selector
			selWindowRen.h = TILE_DIM;
			selWindowRen.w = TILE_DIM;
			selWindowRen.x = selOffX - (spriteDest.x % TILE_DIM);
			selWindowRen.y = selOffY - (spriteDest.y % TILE_DIM);
			break;*/
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