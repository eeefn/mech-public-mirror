
#pragma once
#include "GameObject.h"
#include <SDL.h>
class RockObject : public GameObject{
    public:
        RockObject(short id, int xT, int yT, short rockType);
        void handleClick(Item* clickedBy);

};