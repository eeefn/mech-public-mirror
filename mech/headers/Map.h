#pragma once
#include "./constants.h"
#include "./GameObject.h"
#include "stdlib.h"
#include <SDL.h>

#include <vector>
#include <string>
#include <memory>


class Map {
public:
	short tileMap[MAX_LVL_HEIGHT][MAX_LVL_WIDTH];
	std::vector<std::shared_ptr<GameObject>> gameObjList;
	//read the map
	bool read(std::string mapIn);
	bool fill(SDL_Rect selWindowRen, int xOffset,int yOffset, int selectColor);
	bool save(std::string mapIn);
	bool initGameObject();
	void initialize();
	//constructors. map(string) is unused rn
	Map(std::string mapIn);
	Map();
};
extern Map map;