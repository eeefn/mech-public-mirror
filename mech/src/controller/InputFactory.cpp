#include "../../headers/controller/InputFactory.h"
#include "../../headers/controller/EditInput.h"
#include "../../headers/controller/PlayInput.h"
#include "../../headers/controller/MechInput.h"
#include "../../headers/controller/SoulSpriteInput.h"
#include "../../headers/constants.h"

#include <iostream>

InputFactory inputFactory;

InputFactory::InputFactory(){
}

bool InputFactory::processInput(SDL_Event *event, int *gameMode){
    bool gameIsRunning = true;
    if(lockTime == 0){
        if(*gameMode == gamemodes.EDIT){
            gameIsRunning = editInput.processInput(event,gameMode);
        }
        else if(*gameMode == gamemodes.PLAY){
            if (controlMode == controlModes.PLAYER){
                gameIsRunning = playInput.processInput(event, gameMode);
            }
            else if(controlMode == controlModes.SOUL_SPRITE){
                gameIsRunning = soulSpriteInput.processInput(event, gameMode);
            }
            else if(controlMode == controlModes.MECH){
                gameIsRunning = mechInput.processInput(event, gameMode);
            }
        }
    }
    else{
        if(event->type == SDL_KEYDOWN && event->key.repeat == 0){
            switch(event->key.keysym.sym){
                case SDLK_ESCAPE:
                    gameIsRunning = false;
                    break;
                case SDLK_a:
                    moveLeftCount++;
                    break;
                case SDLK_d:
                    moveRightCount++;
                    break;
            }
        }
        if(event->type == SDL_KEYUP){
            switch(event->key.keysym.sym){
                case SDLK_a:
                    moveLeftCount--;
                    break;
                case SDLK_d:
                    moveRightCount--;
                    break;
            }
        }
    }
    return gameIsRunning;
}

void InputFactory::addLockTime(int reqLockTime){
    lockTime = lockTime + reqLockTime;
}

void InputFactory::update(){
    if(lockTime > 0){
        lockTime--;
    }
    else{
        SDL_Event ev;
        ev.type = SDL_KEYDOWN;
        ev.key.repeat = 0;
        if(moveLeftCount > 0){
            moveLeftCount = 0;
            ev.key.keysym.sym = SDLK_a;
            SDL_PushEvent(&ev);
        }
        if(moveRightCount > 0){
            moveRightCount = 0;
            ev.key.keysym.sym = SDLK_d;
            SDL_PushEvent(&ev);
        }
    }
}
void InputFactory::setControlMode(int mode){
    controlMode = mode;
}