#include "Mech.h"
#include "stdio.h"
#include <iostream>


Mech mech;

using std::cout;

Mech::Mech() {
	
	//init rectangles
	cout << "initializing mech" << '\n';
	for (unsigned int i = 0; i < 3; i++) {
		for (unsigned int j = 0; j < 59; j++) {
			mechArr[i][j].x = j * 96;
			mechArr[i][j].y = i * 144;
			mechArr[i][j].w = 96;
			mechArr[i][j].h = 144;
		}
	}
	posX = 100;
	posY = 100;
	isPlayer = false;
	velX, velY = 0;
	accX = 0;
	accY = 250;
	dispRect.x = 100;
	dispRect.y = 100;	
	dispRect.w = 96 * 2;
	dispRect.h = 144 * 2;
	
}

void Mech::renderMech(SDL_Renderer* rend) {
	SDL_RenderCopy(rend, mechTex, &mechArr[2][0],&dispRect);
	SDL_RenderCopy(rend, mechTex, &mechArr[3][0], &dispRect);
}

void Mech::updateMech(float dt) {
	if (accY > 250) {
		accY = 250;
	}
	velY += accY * dt;
	if (velY >= MAX_VEL) {
		velY = MAX_VEL;
	}
	posX += round(velX * dt);
	posY += round(velY * dt);
	dispRect.x = posX;
	dispRect.y = posY;
}

void Mech::processCollision(bool collisions[4]) {
	if (collisions[0]) {
		mech.posY = (mech.posY) / TILE_DIM * TILE_DIM;
		mech.velY = 0;
	}
}