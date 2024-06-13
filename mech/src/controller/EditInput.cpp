#include "../../headers/controller/EditInput.h"
#include "../../headers/Map.h"
#include "../../headers/Gui.h"
#include "../../headers/Camera.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>

EditInput editInput;

EditInput::EditInput(){
    return;
}

bool EditInput::processInput(SDL_Event *keydownEvent, int *gameMode){
    bool gameIsRunning = true;    
    if(keydownEvent->type == SDL_KEYDOWN){
        gameIsRunning = this->processKeydown(keydownEvent,gameMode);
    }
    if(keydownEvent->type == SDL_QUIT){
        gameIsRunning = false;
    }
    return gameIsRunning;
}

int EditInput::processKeydown(SDL_Event *keydownEvent, int *gameMode){
    bool gameIsRunning = true;
    switch (keydownEvent->key.keysym.sym) {
		case SDLK_e: 
            *gameMode = PLAY;
            break;
		case SDLK_RIGHT: gui.expandSelWindowRight(); break;
		case SDLK_LEFT:
			gui.expandSelWindowLeft();
			break;
		case SDLK_DOWN: gui.expandSelWindowDown(); break;
		case SDLK_UP: gui.expandSelWindowUp(); break;
        case SDLK_a: gui.moveSelWindowLeft(); break;
        case SDLK_d: gui.moveSelWindowRight(); break;
        case SDLK_s: gui.moveSelWindowDown(); break;
        case SDLK_w: gui.moveSelWindowUp; break;
        case SDLK_0: gui.selectColor = 0; break;
        case SDLK_1: gui.selectColor = 1; break;
        case SDLK_2: gui.selectColor = 2; break;
        case SDLK_3: gui.selectColor = 3; break;
        case SDLK_f: map.fill(gui.selWindowRen,camera.xOffset,camera.yOffset,gui.selectColor); break;
        case SDLK_z: map.save("lvl1Test.bin"); break;
        case SDLK_ESCAPE: 
            gameIsRunning = false; 
            break;

	}
    return gameIsRunning;
}