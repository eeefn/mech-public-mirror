#include <SDL.h>
#include "../headers/Collider.h"
#include "../headers/Camera.h"
#include "../headers/constants.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

Collider collider;

Collider::Collider() {
	yLen = 0;
	xLen = 0;
	xTilePos = 0;
	yTilePos = 0;
	for (unsigned int i = 0; i < 4; i++) {
		colResults[i] = false;
	}
}

bool Collider::collisionCheck(Entity* entity, short tileMap[][mapInfo.MAX_LVL_WIDTH]) {
	bool colOccur = false;
	//reset collision results
	for (unsigned int i = 0; i < 4; i++) {
		colResults[i] = false;
	}
	//assign the number of tiles tall the collison box is. same for width of collision box
	xTilePos = entity->posX / mapInfo.TILE_DIM;
	yTilePos = entity->posY / mapInfo.TILE_DIM;
	yLen = (entity->entityHeight) / mapInfo.TILE_DIM;
	xLen =  (entity->entityWidth) / mapInfo.TILE_DIM;
	//if going down
	if (entity->velY > 0) {
		//iterate through the bottom  x tiles to check for collision
		for (short i = xTilePos; i < (xTilePos + xLen); i++) {
			if (tileMap[yTilePos + yLen][i] > 0) {
				//cout << "collison down at " << xTilePos << ", " << yLen << '\n';
				colResults[0] = true;
				colOccur = true;
			}
		}
	}//if going up
	else {
		for (short i = xTilePos; i < (xTilePos + xLen); i++) {
			if (tileMap[yTilePos][i]) {
				colResults[1] = true;
				colOccur = true;
			}
		}
	}
	if (entity->velX > 0) {
		//moving right
		for (unsigned int i = yTilePos; i < (yTilePos + yLen); i++) {
			if (tileMap[i][xTilePos + xLen] > 0) {
				colResults[2] = true;
				colOccur = true;
			}
		}
	}
	else if (entity->velX < 0){
		//moving left
		for (unsigned int i = yTilePos; i < (yTilePos + yLen); i++) {
			if (tileMap[i][xTilePos] > 0) {
				colResults[3] = true;
				//cout << "collison left at " << xTilePos << ", " << i << '\n';
				colOccur = true;
			}
		}
	}
	return colOccur;
}