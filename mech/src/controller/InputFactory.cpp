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
    setLockStatus(event);
    if(!inputLock){
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
        if(event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_ESCAPE){
            gameIsRunning = false;
        }
    }
    return gameIsRunning;
}

void InputFactory::setLockStatus(SDL_Event *event){
    if(event->type == SDL_USEREVENT){
        if(event->user.code == userEvents.LOCK_INPUTS){
            inputLock = true;
        }
        else if(event->user.code == userEvents.UNLOCK_INPUTS){
            inputLock = false;
        }
    }
}
void InputFactory::setControlMode(int mode){
    controlMode = mode;
}