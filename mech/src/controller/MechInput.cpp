#include "../../headers/controller/MechInput.h"
#include "../../headers/Camera.h"
#include "../../headers/entities/Entity.h"

MechInput mechInput;

MechInput::MechInput(){

}

bool MechInput::processInput(SDL_Event *keyEvent, int *gameMode){
	bool gameIsRunning = true;
	if (keyEvent->type == SDL_KEYDOWN && keyEvent->key.repeat == 0) {
		gameIsRunning = mechInput.processKeydown(keyEvent, gameMode);
	}
	if (keyEvent->type == SDL_MOUSEBUTTONDOWN) {
		mechInput.processMousedown(keyEvent);
	}
	if (keyEvent->type == SDL_KEYUP && keyEvent->key.repeat == 0) {
		mechInput.processKeyup(keyEvent);
	}
	else if (keyEvent->type == SDL_QUIT) {
        gameIsRunning = false;
	}
    return gameIsRunning;
}

int MechInput::processKeydown(SDL_Event *keyDownEvent, int *gameMode){
    bool gameIsRunning = true;
    Entity *playerEntity = camera.cameraTarget;
    switch (keyDownEvent->key.keysym.sym) {
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
        case SDLK_q:
            break;
		case SDLK_ESCAPE: gameIsRunning = false; break;
    }
    return gameIsRunning;    
}

void MechInput::processMousedown(SDL_Event *mouseDownEvent){
	Entity *playerEntity = camera.cameraTarget;
	switch (mouseDownEvent->button.button) {
		case SDL_BUTTON_RIGHT:
			playerEntity->attackRight(mouseDownEvent->button.x);
			break;
	}
}

void MechInput::processKeyup(SDL_Event *keyupEvent){
	Entity *playerEntity = camera.cameraTarget;
	switch (keyupEvent->key.keysym.sym) {
		case SDLK_a:
			playerEntity->moveLeft(false);
			break;
		case SDLK_d:
			playerEntity->moveRight(false);
			break;
    }
}