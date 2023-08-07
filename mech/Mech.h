#pragma once
#include "./constants.h"
#include "./Entity.h"
#include <SDL.h>

#define MAX_VEL 200
#define MECH_WIDTH 96 * 2
#define MECH_HEIGHT 144 * 2
class Mech : public Entity 
{
	//size of the sheet
	public:
		bool highlighted;
		Mech();
		SDL_Rect mechArr[4][60];
		SDL_Rect dispRect;
		SDL_Texture* mechTex;
		bool poweredUp, stood;
		int currFrame,playFrame;
		void updateEntity(float dt, int yO,int xO,int pPos);
		void moveLeft(bool key);
		void moveRight(bool key);
		void renderMech(SDL_Renderer* rend);
		void processCollision(bool collisions[4]);
};
extern Mech mech;
