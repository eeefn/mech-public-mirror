#include "../headers/Collider.h"
#include <SDL.h>
#include "../headers/constants.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using std::cout;

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

bool Collider::collisionCheck(int xPos, int yPos, int entityWidth, int entityHeight, float yVel, float xVel, short tileMap[][MAX_LVL_WIDTH],int xOffset, int yOffset) {
	bool colOccur = false;
	//reset collision results
	for (unsigned int i = 0; i < 4; i++) {
		colResults[i] = false;
	}
	//assign the number of tiles tall the collison box is. same for width of collision box
	//cout << "x,y:" << '\n';
	//cout << xPos << " " << yPos << '\n';
	xTilePos = xPos / TILE_DIM;
	yTilePos = yPos / TILE_DIM;
	//cout << "tile x, y:" << '\n';
	//cout << xTilePos << " " << yTilePos << '\n';
	yLen = (entityHeight) / TILE_DIM;
	xLen = (entityWidth) / TILE_DIM;
	//cout << "len x, y:" << '\n';
	//cout << xLen << " " << yLen << '\n';
	//grab the x pos in tilemap. This will need to include offset in a sec.//i think these operations need to be floored
	
	//if going down
	if (yVel > 0) {
		//iterate through the bottom  x tiles to check for collision
		//cout << "checking " << xTilePos << " through " << xTilePos + xLen << " at "<< yTilePos + yLen << '\n';
		
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
	if (xVel > 0) {
		//cout << "MR";
		//moving right
		for (unsigned int i = yTilePos; i < (yTilePos + yLen); i++) {
			if (tileMap[i][xTilePos + xLen] > 0) {
				colResults[2] = true;
				colOccur = true;
			}
		}
	}
	else if (xVel < 0){
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