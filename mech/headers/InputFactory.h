#pragma once

class InputFactory{
    public:
        int *gameMode;
        bool processInput();
        InputFactory(int *gameMode);
};