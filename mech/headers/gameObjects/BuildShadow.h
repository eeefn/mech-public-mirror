#pragma once
#include "GameObject.h"

class BuildShadow{
    public:
        BuildShadow();
        ~BuildShadow();
        void render();
        void update();
        void setShadowObject(short objectType);
        bool placeShadowObject();
        void destroyShadowObject();
        bool validPlacement;
    private:
        bool checkValidPlacement();
        void snapCenterPoint(SDL_Point* pointToSnapAndCenter);
        GameObject* shadowObject;
};