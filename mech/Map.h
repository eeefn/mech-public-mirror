#pragma once
#include "./constants.h"
#include "stdlib.h"
#include <string>

class Map {
public:
	short tileMap[MAX_LVL_HEIGHT][MAX_LVL_WIDTH];
	bool read(std::string mapIn);
	bool fill();
	bool save();
	Map(std::string mapIn);
	Map();
};
extern Map map;