#pragma once
#include "GameObject.h"
#include <SDL.h>

class TallGrassObject : public GameObject{
    public:
        TallGrassObject(short id, int xT, int yT, short grassType);
        void handleClick(Item* clickedBy);
};