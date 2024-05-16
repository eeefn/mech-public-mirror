#include "../../headers/controller/InputFactory.h"
#include "../../headers/controller/EditInput.h"
#include "../../headers/controller/PlayInput.h"
#include "../../headers/constants.h"


#include <stdlib.h>
#include <stdio.h>
#include <iostream>

InputFactory::InputFactory(SDL_Event *event, int *gameMode,vector<Entity*> *entityList){
    this->gameMode = gameMode;
    this->event = event;
    this->entityList = entityList;
    return;
}

bool InputFactory::processInput(){
    bool gameIsRunning = true;
    if(*this->gameMode == EDIT){
        gameIsRunning = editInput.processInput(this->event,this->gameMode);
    }
    else if(*this->gameMode == PLAY){
        gameIsRunning = playInput.processInput(this->event,this->entityList,this->gameMode);
    }
    return gameIsRunning;
}