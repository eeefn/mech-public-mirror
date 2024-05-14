#include "../headers/InputFactory.h"
#include "../headers/EditInput.h"
#include "../headers/constants.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

InputFactory::InputFactory(int *gameMode){
    this->gameMode = gameMode;
    return;
}

bool InputFactory::processInput(){
    bool gameIsRunning = true;
    if(*this->gameMode == EDIT){
        //gameIsRunning = editInput.processInput();
    }
    else if(*this->gameMode == PLAY){
        //gameIsRunning = playInput.processInput();
    }
    return gameIsRunning;
}