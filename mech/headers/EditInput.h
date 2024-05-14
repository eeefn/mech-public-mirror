#pragma once
#include <SDL.h>
#include <vector>


#include "../headers/Entity.h"
using std::vector;

class EditInput{
    public:
        int processKeydown();
        EditInput();
};

extern EditInput editInput;