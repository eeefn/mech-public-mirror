#include "../headers/Map.h"
#include "../headers/constants.h"
#include "../headers/gameObjects/Mushroom.h"
#include "../headers/Camera.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <algorithm>

Map map;

Map::Map() {
	initialize();
}

Map::~Map(){
	for(auto gameObj : gameObjList){
		delete gameObj;
	}
	gameObjList.clear();
}
void Map::initialize(){
	tileMap[24][20] = -1;
	initGameObject();
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

void Map::removeObject(GameObject* objToRemove){
	auto objIterator = find(gameObjList.begin(),gameObjList.end(),objToRemove);
	if(objIterator != gameObjList.end()){
		gameObjList.erase(objIterator);	
	}
	delete objToRemove;	
}

GameObject* Map::getFirstHighlightedObject(){
	for(auto gameObj : gameObjList){
		if(gameObj->highlighted){
			return gameObj;
		}	
	}
	return nullptr;
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

bool Map::initGameObject() {
	for (unsigned int i = 0; i < mapInfo.MAX_LVL_HEIGHT; i++) {
		for (unsigned int j = 0; j < mapInfo.MAX_LVL_WIDTH; j++) {
			//check to see if the tile is an object.
			if (this->tileMap[i][j] < 0) {
				short obj = this->tileMap[i][j] * -1;
				//- values represent objects in the tilemap
				if (obj > 0 &&  obj < 15) {
					//construct a mushroom
					Mushroom* mushPtr = new Mushroom(obj,0,j,i);
					gameObjList.push_back(mushPtr);
				}
			}
		}
	}
	return true;
}


void Map::manageHighlightedObjects(SDL_Rect* hitBox){
	for (auto gameObject : gameObjList){
		if (checkObjectCollision(hitBox, &gameObject->renObj)){
			gameObject->highlight(true);
		}else{
			gameObject->highlight(false);
		}
	}	
}

bool Map::checkObjectCollision(SDL_Rect* hitBox1,SDL_Rect* hitBox2) const{
	if ((hitBox1->x < hitBox2->x + hitBox2->w) && (hitBox1->x + hitBox1->w > hitBox2->x)){
		if ((hitBox1->y < hitBox2->y + hitBox2->h) && (hitBox1->y + hitBox1->h > hitBox2->y)){
			return true;
		}
	}
	return false;
}

