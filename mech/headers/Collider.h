#pragma once
#include "./constants.h"
#include "./entities/Entity.h"
#include <SDL.h>

class Collider
{
public:
	int yLen, xLen;
	int xTilePos, yTilePos;
	bool colResults[4];
	Collider();
	bool collisionCheck(Entity* entity, short tileMap[][mapInfo.MAX_LVL_WIDTH]);
	bool checkObjectCollision(SDL_Rect* hitBox1, SDL_Rect* hitBox2) const;

};

extern Collider collider;