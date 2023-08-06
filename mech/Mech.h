#pragma once
#include "./constants.h"
#include <SDL.h>

#define MAX_VEL 200
#define MECH_WIDTH 96 * 2
#define MECH_HEIGHT 144 * 2
class Mech
{
	//size of the sheet
	public:
		int posX, posY;
		int velX, velY;
		int accX, accY;
		bool isPlayer;
		Mech();
		SDL_Rect mechArr[4][60];
		SDL_Rect dispRect;
		SDL_Texture* mechTex;
		void updateMech(float dt);
		void renderMech(SDL_Renderer* rend);
		void processCollision(bool collisions[4]);
};
extern Mech mech;
