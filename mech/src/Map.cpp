#include "../headers/Map.h"
#include "../headers/constants.h"
#include "../headers/Mushroom.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>


Map map;

Map::Map(std::string mapIn) {
	if (!this->read(mapIn)) {
		std::cout << "map read failiure" << '\n';
	}
}

Map::Map() {

}

bool Map::read(std::string mapIn) {
	std::ifstream mapStream(mapIn, std::ios::in | std::ios::binary);
	if (mapStream.good()) {
		for (unsigned int i = 0; i < MAX_LVL_HEIGHT; i++) {
			for (unsigned int j = 0; j < MAX_LVL_WIDTH; j++) {
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

bool Map::fill(SDL_Rect selWindowRen, int xOffset, int yOffset, int selectColor) {
	for (int i = selWindowRen.y / TILE_DIM + yOffset; i < (selWindowRen.h / TILE_DIM) + (selWindowRen.y / TILE_DIM + yOffset); i++) {
		for (int j = selWindowRen.x / TILE_DIM + xOffset; j < (selWindowRen.w / TILE_DIM) + (selWindowRen.x / TILE_DIM + xOffset); j++) {
			//cout << "i is: " << i << ". j is: " << j << '\n';
			this->tileMap[i][j] = selectColor;
		}
	}
	return true;
}

bool Map::save(std::string mapIn) {
	std::ofstream file(mapIn, std::ios::trunc | std::ios::out | std::ios::binary);
	for (unsigned int i = 0; i < MAX_LVL_HEIGHT; i++) {
		for (unsigned int j = 0; j < MAX_LVL_WIDTH; j++) {
			file.write((char*)&this->tileMap[i][j], sizeof(short));
		}
	}
	file.close();
	return true;
}

bool Map::initGameObject() {
	for (unsigned int i = 0; i < MAX_LVL_HEIGHT; i++) {
		for (unsigned int j = 0; j < MAX_LVL_WIDTH; j++) {
			//check to see if the tile is an object.
			if (this->tileMap[i][j] < 0) {
				short obj = this->tileMap[i][j] * -1;
				//- values represent objects in the tilemap
				if (obj > 0 &&  obj < 15) {
					//construct a mushroom
					std::cout << "constructed mushroom " << '\n';
					gameObjList.push_back(std::make_shared<Mushroom>(obj,0,j,i));
				}
			}
		}
	}
	return true;
}



