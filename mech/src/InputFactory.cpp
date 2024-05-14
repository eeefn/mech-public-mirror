#include "../headers/InputFactory.h"
#include "../headers/EditInput.h"
#include "../headers/PlayInput.h"
#include "../headers/constants.h"


#include <stdlib.h>
#include <stdio.h>
#include <iostream>

InputFactory::InputFactory(SDL_Event *event,int *xOffset, int *yOffset, int *gameMode,vector<Entity*> *entityList, SDL_Rect *spriteDest){
    this->gameMode = gameMode;
    this->event = event;
    this->xOffset = xOffset;
    this->yOffset = yOffset;
    this->entityList = entityList;
    this->spriteDest = spriteDest;
    return;
}

bool InputFactory::processInput(){
    bool gameIsRunning = true;
    if(*this->gameMode == EDIT){
        gameIsRunning = editInput.processInput(this->event,this->xOffset,this->yOffset,this->gameMode);
    }
    else if(*this->gameMode == PLAY){
        gameIsRunning = playInput.processInput(this->event,this->entityList,this->spriteDest,this->gameMode);
    }
    return gameIsRunning;
}