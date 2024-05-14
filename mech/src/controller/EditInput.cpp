#include "../../headers/controller/EditInput.h"
#include "../../headers/Player.h"
#include "../../headers/Map.h"
#include "../../headers/Gui.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

EditInput editInput;

EditInput::EditInput(){
    return;
}

bool EditInput::processInput(SDL_Event *keydownEvent, int *xOffset, int *yOffset, int *gameMode){
    bool gameIsRunning = true;    
    if(keydownEvent->type == SDL_KEYDOWN){
        gameIsRunning = this->processKeydown(keydownEvent,xOffset,yOffset,gameMode);
    }
    if(keydownEvent->type == SDL_QUIT){
        gameIsRunning = false;
    }
    return gameIsRunning;
}

int EditInput::processKeydown(SDL_Event *keydownEvent,int *xOffset, int *yOffset, int *gameMode){
    bool gameIsRunning = true;
    switch (keydownEvent->key.keysym.sym) {
		case SDLK_e: 
            *gameMode = PLAY;
            break;
		case SDLK_RIGHT: gui.selWindowRen.w += TILE_DIM; break;
		case SDLK_LEFT:
			gui.selWindowRen.w -= TILE_DIM;
			if (gui.selWindowRen.w < TILE_DIM) {
				gui.selWindowRen.w = TILE_DIM;
			}
			break;
		case SDLK_DOWN: gui.selWindowRen.h += TILE_DIM; break;
		case SDLK_UP:
            gui.selWindowRen.h -= TILE_DIM;
            if (gui.selWindowRen.h < TILE_DIM) {
                gui.selWindowRen.h = TILE_DIM;
            }
            break;
        case SDLK_a: 
            gui.selWindowRen.x -= TILE_DIM;
            if (gui.selWindowRen.x <= 0) {
                gui.selWindowRen.x = 0;
            }
            break;
        case SDLK_d: gui.selWindowRen.x += TILE_DIM; break;
        case SDLK_s: gui.selWindowRen.y += TILE_DIM; break;
        case SDLK_w: 
            gui.selWindowRen.y -= TILE_DIM;
            if (gui.selWindowRen.y <= 0) {
                gui.selWindowRen.y = 0;
            }
            break;
        case SDLK_0: gui.selectColor = 0; break;
        case SDLK_1: gui.selectColor = 1; break;
        case SDLK_2: gui.selectColor = 2; break;
        case SDLK_3: gui.selectColor = 3; break;
        case SDLK_f: map.fill(gui.selWindowRen,*xOffset,*yOffset,gui.selectColor); break;
        case SDLK_z: map.save("lvl1Test.bin"); break;
        case SDLK_ESCAPE: 
            gameIsRunning = false; 
            break;

	}
    return gameIsRunning;
}