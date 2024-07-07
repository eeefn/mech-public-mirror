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
		std::vector<std::shared_ptr<GameObject>> gameObjList;
		//read the map
		bool checkObjectCollision(SDL_Rect* hitBox1, SDL_Rect* hitBox2) const;
		void manageHighlightedObjects(SDL_Rect* hitBox);
		bool read(std::string mapIn);
		bool fill(SDL_Rect* selWindowRen, int xOffset,int yOffset, int selectColor);
		bool save(std::string mapIn);
		Map();
	private:
		std::vector<std::shared_ptr<GameObject>> highlightedList;
		void initialize();
		bool initGameObject();
};
extern Map map;