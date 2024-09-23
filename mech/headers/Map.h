#pragma once
#include "./constants.h"
#include "gameObjects/GameObject.h"
#include "stdlib.h"
#include <SDL.h>

#include <vector>
#include <string>
#include <memory>


class Map {
	public:
		std::vector<GameObject*> gameObjList;
		short tileMap[mapInfo.MAX_LVL_HEIGHT][mapInfo.MAX_LVL_WIDTH];
		bool read(std::string mapIn);
		bool fill(SDL_Rect* selWindowRen);
		bool save(std::string mapIn);
		Map();
		~Map();
		int tileType = 0;
		void initialize();
	private:
		bool readGameObjectsFromMap();
};
extern Map map;