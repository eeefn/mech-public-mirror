#include "Mech.h"
#include "stdio.h"
#include <iostream>


Mech mech;

using std::cout;

Mech::Mech() {
	
	//init rectangles
	//cout << "initializing mech" << '\n';
	for (unsigned int i = 0; i < 4; i++) {
		for (unsigned int j = 0; j < 59; j++) {
			mechArr[i][j].x = j * 96;
			mechArr[i][j].y = i * 144;
			mechArr[i][j].w = 96;
			mechArr[i][j].h = 144;
		}
	}
	posX = 400; posY = 80;
	isPlayer = false; inAir = false;
	velX, velY = 0;
	currFrame, playFrame = 0;
	accX = 0; accY = 250;
	dispRect.x, dispRect.y = 100;	
	dispRect.w = 96 * 2;
	dispRect.h = 144 * 2;
	highlighted = true;
	poweredUp, stood = false;
	entitySpeedX = 70;
}

void Mech::renderMech(SDL_Renderer* rend) {
	if (!mech.isPlayer) {
		SDL_RenderCopy(rend, mechTex, &mechArr[2][0], &dispRect);
		SDL_RenderCopy(rend, mechTex, &mechArr[3][0], &dispRect);
		if (highlighted) {
			SDL_RenderCopy(rend, mechTex, &mechArr[1][30], &dispRect);
		}
	}
	else {
		if (!poweredUp) {
			playFrame = currFrame / 4;
			SDL_RenderCopy(rend, mechTex, &mechArr[2][playFrame], &dispRect);
			SDL_RenderCopy(rend, mechTex, &mechArr[3][playFrame], &dispRect);
			cout << "powering up at frame: " << currFrame << '\n';
			currFrame++;
			if (currFrame >= 240) {
				poweredUp = true;
				currFrame = 0;
			}
		}
		else if(!stood) {
			playFrame = currFrame / 2;
			cout << "standing up at frame: " << currFrame << '\n';
			SDL_RenderCopy(rend, mechTex, &mechArr[0][playFrame], &dispRect);
			SDL_RenderCopy(rend, mechTex, &mechArr[1][playFrame], &dispRect);
			currFrame++;
			if (currFrame >= 59) {
				stood = true;
				playFrame = 29;
			}
		}
		else {
			SDL_RenderCopy(rend, mechTex, &mechArr[0][playFrame], &dispRect);
			SDL_RenderCopy(rend, mechTex, &mechArr[1][playFrame], &dispRect);
		}
		
	}
	
}

void Mech::moveLeft(bool key) {
	if (key) {
		velX -= entitySpeedX;
	}
	else {
		velX += entitySpeedX;
	}

}

void Mech::moveRight(bool key) {
	if (key) {
		velX += entitySpeedX;
	}
	else {
		velX -= entitySpeedX;
	}
}
void Mech::updateEntity(float dt, int yO, int xO, int pPosX) {
	//
	Entity::updateEntity(dt);
	//update the position of the display rectangle to indicate screen coords
	if (pPosX > (WINDOW_WIDTH / 2 - 64 / 2)) {
		dispRect.x = posX - (pPosX - (WINDOW_WIDTH/2 - 64/2));
	}
	else {
		dispRect.x = posX;
	}
	//dispRect.x = posX - (xO * 16);
	dispRect.y = posY - (yO * 16);
}

void Mech::processCollision(bool collisions[4]) {
	if (collisions[0]) {
		mech.posY = (mech.posY) / TILE_DIM * TILE_DIM;
		mech.velY = 0;
	}
}