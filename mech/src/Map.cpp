#include "../headers/Map.h"
#include "../headers/constants.h"
#include "../headers/gameObjects/gameObjectManager.h"
#include "../headers/gameObjects/Mushroom.h"
#include "../headers/Camera.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <algorithm>

Map map;

Map::Map() {
}

Map::~Map(){
}

void Map::initialize(){
	tileMap[24][20] = -1;
	readGameObjectsFromMap();
	read("../resources/lvl1Test.bin");
}

bool Map::read(std::string mapIn) {
	std::ifstream mapStream(mapIn, std::ios::in | std::ios::binary);
	if (mapStream.good()) {
		for (unsigned int i = 0; i < mapInfo.MAX_LVL_HEIGHT; i++) {
			for (unsigned int j = 0; j < mapInfo.MAX_LVL_WIDTH; j++) {
				mapStream.read((char*)&this->tileMap[i][j], sizeof(short));
			}
		}
		mapStream.close();
		return true;
	}
	else {
		return false;
	}
}

bool Map::fill(SDL_Rect* selWindowRen) {
	for (int i = selWindowRen->y / mapInfo.TILE_DIM + camera.yOffset; i < (selWindowRen->h / mapInfo.TILE_DIM) + (selWindowRen->y / mapInfo.TILE_DIM + camera.yOffset); i++) {
		for (int j = selWindowRen->x / mapInfo.TILE_DIM + camera.xOffset; j < (selWindowRen->w / mapInfo.TILE_DIM) + (selWindowRen->x / mapInfo.TILE_DIM + camera.xOffset); j++) {
			this->tileMap[i][j] = tileType;
		}
	}
	return true;
}

bool Map::save(std::string mapIn) {
	std::ofstream file(mapIn, std::ios::trunc | std::ios::out | std::ios::binary);
	for (unsigned int i = 0; i < mapInfo.MAX_LVL_HEIGHT; i++) {
		for (unsigned int j = 0; j < mapInfo.MAX_LVL_WIDTH; j++) {
			file.write((char*)&this->tileMap[i][j], sizeof(short));
		}
	}
	file.close();
	return true;
}

bool Map::readGameObjectsFromMap() {
	for (unsigned int i = 0; i < mapInfo.MAX_LVL_HEIGHT; i++) {
		for (unsigned int j = 0; j < mapInfo.MAX_LVL_WIDTH; j++) {
			//check to see if the tile is an object.
			if (this->tileMap[i][j] < 0) {
				short obj = this->tileMap[i][j] * -1;
				//- values represent objects in the tilemap
				gameObjectManager.makeObject(obj,j,i);
				/*if (obj > 0 &&  obj < 15) {
					//construct a mushroom
					Mushroom* mushPtr = new Mushroom(obj,0,j,i);
					gameObjList.push_back(mushPtr);
    
				}*/
			}
		}
	}
	return true;
}