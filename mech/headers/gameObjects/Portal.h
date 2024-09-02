#pragma once
#include "GameObject.h"
#include <SDL.h>
#include "../Animator.h"

class Portal : public GameObject{
    public:
        Portal(short id,int xT,int yT);
        bool activate();
        void render(SDL_Renderer *rend);
		bool highlight(const std::string& srcEntityId);
        void update();
        bool active = false;
        Animator anim;
        Animator::AnimSelect discs{0,0};
        Animator::AnimSelect beam{1,0};
        SDL_Rect portalAnimRect[2][55];
};