#pragma once
#include <SDL.h>

class WindowManager{
    public:
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;
        bool initializeWindow(); 
        void destroyWindow();
};

extern WindowManager windowManager;