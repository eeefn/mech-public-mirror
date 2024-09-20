#include <SDL.h>
#include "../headers/Collider.h"
#include "../headers/Camera.h"
#include "../headers/Map.h"
#include "../headers/constants.h"
Collider collider;

Collider::Collider() {

}

bool Collider::checkItemTileMapCollision(Item* item){
	bool colOccur = false;
	for (unsigned int i = 0; i < 4; i++) {
		colResults[i] = false;
	}
	int xTilePos = item->xPos / mapInfo.TILE_DIM;
	int yTilePos = item->yPos / mapInfo.TILE_DIM;
	int yLen = 16*2 / mapInfo.TILE_DIM;
	int xLen =  16*2 / mapInfo.TILE_DIM;
	for (short i = xTilePos; i < (xTilePos + xLen); i++) {
		if (map.tileMap[yTilePos + yLen][i] > 0) {
			colResults[0] = true;
			colOccur = true;
		}
	}
	return colOccur;	
}

bool Collider::checkEntityTileMapCollision(Entity* entity) {
	bool colOccur = false;
	//reset collision results
	for (unsigned int i = 0; i < 4; i++) {
		colResults[i] = false;
	}
	//assign the number of tiles tall the collison box is. same for width of collision box
	int xTilePos = entity->posX / mapInfo.TILE_DIM;
	int yTilePos = entity->posY / mapInfo.TILE_DIM;
	int yLen = (entity->entityHeight) / mapInfo.TILE_DIM;
	int xLen =  (entity->entityWidth) / mapInfo.TILE_DIM;
	//if going down
	if (entity->velY > 0) {
		//iterate through the bottom  x tiles to check for collision
		for (short i = xTilePos; i < (xTilePos + xLen); i++) {
			if (map.tileMap[yTilePos + yLen][i] > 0) {
				colResults[0] = true;
				colOccur = true;
			}
		}
	}
	else {
		for (short i = xTilePos; i < (xTilePos + xLen); i++) {
			if (map.tileMap[yTilePos][i]) {
				colResults[1] = true;
				colOccur = true;
			}
		}
	}
	if (entity->velX > 0) {
		//moving right
		for (short int i = yTilePos; i < (yTilePos + yLen); i++) {
			if (map.tileMap[i][xTilePos + xLen] > 0) {
				colResults[2] = true;
				colOccur = true;
			}
		}
	}
	else if (entity->velX < 0){
		//moving left
		for (short int i = yTilePos; i < (yTilePos + yLen); i++) {
			if (map.tileMap[i][xTilePos] > 0) {
				colResults[3] = true;
				colOccur = true;
			}
		}
	}
	return colOccur;
}

bool Collider::checkRectRectCollision(SDL_Rect* hitBox1,SDL_Rect* hitBox2) const{
	if ((hitBox1->x < hitBox2->x + hitBox2->w) && (hitBox1->x + hitBox1->w > hitBox2->x)){
		if ((hitBox1->y < hitBox2->y + hitBox2->h) && (hitBox1->y + hitBox1->h > hitBox2->y)){
			return true;
		}
	}
	return false;
}

bool Collider::checkPointWithinRect(int xPos,int yPos,SDL_Rect &renObj){
	if(xPos >= renObj.x && xPos <= renObj.x + renObj.w){
		if(yPos >= renObj.y && yPos <= renObj.y + renObj.h){
			return true;		
		}
	}
	return false;
}

bool Collider::checkGameObjectTileMapCollision(GameObject* gameObject){
	int xStop = gameObject->xTile + gameObject->scaledWidth/mapInfo.TILE_DIM;	
	int yStop = gameObject->yTile + gameObject->scaledWidth/mapInfo.TILE_DIM;
	if(xStop > mapInfo.MAX_LVL_WIDTH || yStop > mapInfo.MAX_LVL_HEIGHT){
		return true;	
	}
	for(int i = gameObject->yTile; i < yStop; i++){
		for(int j = gameObject->xTile; j < xStop; j++){
			if(map.tileMap[i][j] > 0){
				return true;
			}
		}
	}
	return false;	
}