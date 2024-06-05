#include "../../headers/entities/Mech.h"
#include "../../headers/Camera.h"
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
	mechHandArr[0].x = 0; mechHandArr[0].y = 0; mechHandArr[0].w = 7; mechHandArr[0].h = 13;
	handRect[0].x = 0; handRect[0].y = 0; handRect[0].w = 14; handRect[0].h = 26;
	mechHandArr[1].x = 9; mechHandArr[1].y = 0; mechHandArr[1].w = 10; mechHandArr[1].h = 5;
	handRect[1].x = 0; handRect[1].y = 0; handRect[1].w = 20; handRect[1].h = 10;
	mechHandArr[2].x = 9; mechHandArr[2].y = 6; mechHandArr[2].w = 10; mechHandArr[2].h = 7;
	handRect[2].x = 0; handRect[2].y = 0; handRect[2].w = 20; handRect[2].h = 14;
	mechHandArr[3].x = 20; mechHandArr[3].y = 0; mechHandArr[3].w = 17; mechHandArr[3].h = 14;
	handRect[3].x = 0; handRect[3].y = 0; handRect[3].w = 34; handRect[3].h = 28;
	mechHandArr[4].x = 38; mechHandArr[4].y = 4; mechHandArr[4].w = 20; mechHandArr[4].h = 7;
	handRect[4].x = 0; handRect[4].y = 0; handRect[4].w = 40; handRect[4].h = 14;
	posX = 400; posY = 80;
	isPlayer, inAir, grappling,reelOut = false;
	velX, velY = 0;
	currFrame, playFrame = 0;
	accX = 0; accY = 250;
	displayRect.x, displayRect.y = 100;	
	displayRect.w = 96 * 2;
	displayRect.h = 144 * 2;
	gDist = 0;
	highlighted = true;
	poweredUp, stood = false;
	entitySpeedX = 70;
}

void Mech::render(SDL_Renderer* renderer) {
	if (!mech.isPlayer) {
		SDL_RenderCopy(renderer, mechTex, &mechArr[2][0], &displayRect);
		SDL_RenderCopy(renderer, mechTex, &mechArr[3][0], &displayRect);
		
		if (highlighted) {
			SDL_RenderCopy(renderer, mechTex, &mechArr[1][30], &displayRect);
		}
	}
	else {
		if (!poweredUp) {
			playFrame = currFrame / 4;
			SDL_RenderCopy(renderer, mechTex, &mechArr[2][playFrame], &displayRect);
			SDL_RenderCopy(renderer, mechTex, &mechArr[3][playFrame], &displayRect);
			currFrame++;
			if (currFrame >= 240) {
				poweredUp = true;
				currFrame = 0;
			}
		}
		else if(!stood) {
			playFrame = currFrame / 2;
			SDL_RenderCopy(renderer, mechTex, &mechArr[0][playFrame], &displayRect);
			SDL_RenderCopy(renderer, mechTex, &mechArr[1][playFrame], &displayRect);
			currFrame++;
			if (currFrame >= 59) {
				stood = true;
				playFrame = 29;
			}
		}
		else {
			SDL_RenderCopy(renderer, mechTex, &mechArr[0][playFrame], &displayRect);
			SDL_RenderCopy(renderer, mechTex, &mechArr[1][playFrame], &displayRect);
			//render grapple
			if (grappling) {
				for (int i = handRect[3].x-20; i >= handRect[0].x; i-=28) {
					handRect[2].x = i;
					handRect[2].y = posY + 142;
					SDL_RenderCopy(renderer,mechAttatchmentTex,&mechHandArr[2],&handRect[2]);
					
				}
				SDL_RenderCopy(renderer, mechAttatchmentTex, &mechHandArr[3], &handRect[3]);
				for (int i = handRect[3].x-8; i >= handRect[0].x;i-=28) {
					handRect[1].x = i;
					handRect[1].y = posY + 144;
					SDL_RenderCopy(renderer, mechAttatchmentTex, &mechHandArr[1], &handRect[1]);
				}
			}
			else {
				SDL_RenderCopy(renderer, mechAttatchmentTex, &mechHandArr[3], &handRect[3]);
			}
			
			SDL_RenderCopy(renderer, mechAttatchmentTex, &mechHandArr[0], &handRect[0]);
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

void Mech::attackRight(int xClick) {
	cout << xClick << '\n';
	cout << handRect[3].x << '\n';
	if (!grappling) {
		grappling = true;
		reelOut = true;
		gDist = xClick - (handRect[3].x + 34);
		if (gDist <= 0) {
			cout << "Setting to 0" << '\n';
			grappling = false;
			reelOut = false;
			gDist = 0;
		}
		else {
			gDist = xClick;
		}
	}
}

void Mech::updateEntity(float dt) {
	Entity::updateEntity(dt);
	//update the position of the display rectangle to indicate screen coords
	//	handRect[0].x = posX - (pPosX - (WINDOW_WIDTH / 2 - 64 / 2)) + 160;
		
	displayRect.x = camera.getXPosWithinFrame(posX);
	displayRect.y = camera.getYPosWithinFrame(posY);
	handRect[0].y = camera.getYPosWithinFrame(posY) + 150;	
	handRect[3].y = handRect[0].y - 2;
	//this whole section is extremely hacky and i feel shame in my heart
	if (!grappling) {
		handRect[3].x = handRect[0].x + 2;
	}
	else {
		
		if ((handRect[3].x < gDist) && reelOut) {
			handRect[3].x = handRect[3].x + 4;
			return;
		}
		reelOut = false;
		if (handRect[3].x > handRect[0].x) {
			handRect[3].x = handRect[3].x - 4;
			return;
		}
		grappling = false;
	}
	
	
}

void Mech::processCollision(bool collisions[4]) {
	if (collisions[0]) {
		mech.posY = (mech.posY) / TILE_DIM * TILE_DIM;
		mech.velY = 0;
	}
}