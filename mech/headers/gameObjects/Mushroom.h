#pragma once
#include "GameObject.h"
#include <SDL.h>
#include <string>
//create an all new object
//place an existing object from tilemap
class Mushroom : public GameObject
{
    public:
        short mushType;
        Mushroom(short mType, short id, int xT, int yT);
        void render(SDL_Renderer* rend);
        bool highlight(const std::string& srcEntityId);
};