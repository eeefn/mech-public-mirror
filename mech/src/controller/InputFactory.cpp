#include "../../headers/controller/InputFactory.h"
#include "../../headers/controller/EditInput.h"
#include "../../headers/controller/PlayInput.h"
#include "../../headers/controller/SoulSpriteInput.h"
#include "../../headers/constants.h"

InputFactory inputFactory;

InputFactory::InputFactory(){
}

bool InputFactory::processInput(SDL_Event *event, int *gameMode){
    bool gameIsRunning = true;
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
    }
    return gameIsRunning;
}

void InputFactory::setControlMode(int mode){
    controlMode = mode;
}