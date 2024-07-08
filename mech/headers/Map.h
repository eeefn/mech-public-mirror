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
		short tileMap[mapInfo.MAX_LVL_HEIGHT][mapInfo.MAX_LVL_WIDTH];
		std::vector<GameObject*> gameObjList;
		//read the map
		bool checkObjectCollision(SDL_Rect* hitBox1, SDL_Rect* hitBox2) const;
		void manageHighlightedObjects(SDL_Rect* hitBox);
		bool read(std::string mapIn);
		bool fill(SDL_Rect* selWindowRen);
		bool save(std::string mapIn);
		Map();
		int tileType = 0;
	private:
		std::vector<GameObject*> highlightedList;
		void initialize();
		bool initGameObject();
};
extern Map map;