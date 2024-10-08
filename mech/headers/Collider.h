#pragma once
#include "./constants.h"
#include "./entities/Entity.h"
#include "./gameObjects/GameObject.h"
#include "items/Item.h"
#include <SDL.h>

class Collider
{
public:
	bool colResults[4] = {false,false,false,false};
	Collider();
	bool checkEntityTileMapCollision(Entity* entity);
	bool checkGameObjectTileMapCollision(GameObject* gameObject);
	bool checkItemTileMapCollision(Item* item);
	bool checkRectRectCollision(SDL_Rect* hitBox1, SDL_Rect* hitBox2) const;
	bool checkPointWithinRect(int xPos,int yPos,SDL_Rect &renObj);

};

extern Collider collider;