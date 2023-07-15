#pragma once
#include "./constants.h"
#include "stdlib.h"
#include <string>
#include <SDL.h>

class Map {
public:
	short tileMap[MAX_LVL_HEIGHT][MAX_LVL_WIDTH];
	bool read(std::string mapIn);
	bool fill(SDL_Rect selWindowRen,int xOffset,int yOffset, int selectColor);
	bool save(std::string mapIn);
	Map(std::string mapIn);
	Map();
};
extern Map map;