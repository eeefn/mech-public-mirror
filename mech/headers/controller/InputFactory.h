#pragma once


#include <SDL.h>
#include <vector>

using std::vector;

extern struct ControlModes{
    constexpr static int PLAYER = 0;
    constexpr static int EDIT = 1;
    constexpr static int SOUL_SPRITE = 2;
    constexpr static int MECH = 3;
}controlModes;

class InputFactory{
    public:
        bool processInput(SDL_Event *event, int *gameMode);
        InputFactory();
        void setControlMode(int mode);
        void addLockTime(int lockTime);
        void update();
        int controlMode;
    private:
        int lockTime = 0;
        int moveLeftCount = 0;
        int moveRightCount = 0;
};

extern InputFactory inputFactory;