#include "Map.h"
#include "./constants.h"
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
		return true;
	}
	else {
		return false;
	}
}


