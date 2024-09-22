#pragma once
#include "GameObject.h"
#include <SDL.h>
class ShortGrassObject : public GameObject{
    public:
        ShortGrassObject(short id, int xT, int yT, short grassType);
        void handleClick(Item* clickedBy);
};