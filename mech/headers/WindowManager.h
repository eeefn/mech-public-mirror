#pragma once
#include <SDL.h>

extern struct WindowSize {
    constexpr static int WINDOW_WIDTH = 1280;
    constexpr static int WINDOW_HEIGHT = 720;
}windowSize;

class WindowManager{
    public:
        SDL_Window* window = NULL;
        SDL_Renderer* renderer = NULL;
        bool initializeWindow(); 
        void destroyWindow();
};

extern WindowManager windowManager;