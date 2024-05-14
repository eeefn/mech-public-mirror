#include "../headers/EditInput.h"
#include "../headers/Player.h"
#include "../headers/Map.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

EditInput editInput;

EditInput::EditInput(){
    return;
}

int EditInput::processKeydown(SDL_Event *keydownEvent, SDL_Rect *selWindowRen,int *xOffset,int *yOffset,short *selectColor, int *gameMode){
    bool gameIsRunning = true;

    switch (keydownEvent->key.keysym.sym) {
		case SDLK_e: gameMode = PLAY; break;
		case SDLK_RIGHT: selWindowRen->w += TILE_DIM; break;
		case SDLK_LEFT:
			selWindowRen->w -= TILE_DIM;
			if (selWindowRen->w < TILE_DIM) {
				selWindowRen->w = TILE_DIM;
			}
			break;
		case SDLK_DOWN: selWindowRen->h += TILE_DIM; break;
		case SDLK_UP:
            selWindowRen->h -= TILE_DIM;
            if (selWindowRen->h < TILE_DIM) {
                selWindowRen->h = TILE_DIM;
            }
            break;
        case SDLK_a: 
            selWindowRen->x -= TILE_DIM;
            if (selWindowRen->x <= 0) {
                selWindowRen->x = 0;
            }
            break;
        case SDLK_d: selWindowRen->x += TILE_DIM; break;
        case SDLK_s: selWindowRen->y += TILE_DIM; break;
        case SDLK_w: 
            selWindowRen->y -= TILE_DIM;
            if (selWindowRen->y <= 0) {
                selWindowRen->y = 0;
            }
            break;
        case SDLK_0: *selectColor = 0; break;
        case SDLK_1: *selectColor = 1; break;
        case SDLK_2: *selectColor = 2; break;
        case SDLK_3: *selectColor = 3; break;
        case SDLK_f: map.fill(*selWindowRen,*xOffset,*yOffset,*selectColor); break;
        case SDLK_z: map.save("lvl1Test.bin"); break;
        case SDLK_ESCAPE: gameIsRunning = false; break;

	}
    return gameIsRunning;
}