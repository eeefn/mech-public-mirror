#pragma once
#include "./constants.h"
#include <SDL.h>
class Collider
{
public:
	int yLen, xLen;
	int xTilePos, yTilePos;
	bool colResults[4];
	Collider();
	bool collisionCheck(int xPos, int yPos, int entityWidth, int entityHeight, float yVel, float xVel,short tileMap[][MAX_LVL_WIDTH]);

};

extern Collider collider;