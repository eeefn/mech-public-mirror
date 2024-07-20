#include "../../headers/entities/Mech.h"
#include "../../headers/Camera.h"
#include "../../headers/TextureManager.h"
#include "../../headers/entities/AnimationCodes.h"
#include "stdio.h"
#include <iostream>


Mech mech;

using std::cout;
using namespace MechAnimationCodes;

Mech::Mech() {
	entityHeight = MECH_HEIGHT; entityWidth = MECH_WIDTH;
	
	//init rectangles
	for (unsigned int i = 0; i < 4; i++) {
		for (unsigned int j = 0; j < 59; j++) {
			mechAnim[i][j] = {static_cast<int>(j * 96),static_cast<int>(i * 144),96,144};
		}
	}
	inMech = true; 
	displayRect = {100,100,MECH_WIDTH,MECH_HEIGHT};
	mechHandArr[0] = {0,0,7,13}; handRect[0] = {0,0,14,26};
	mechHandArr[1] = {9,0,10,5}; handRect[1] = {0,0,20,10};
	mechHandArr[2] = {9,6,10,7}; handRect[2] = {0,0,20,14};
	mechHandArr[3] = {20,0,17,14}; handRect[3] = {0,0,34,28};
	mechHandArr[4] = {38,4,20,7}; handRect[4] = {0,0,40,14};
	posX = 400; posY = 80;
	isPlayer, inAir, grappling,reelOut,entityTransition = false;
	velX, velY = 0;
	currFrame, playFrame = 0;
	accX = 0; accY = GRAVITY;
	highlighted = true;
	poweredUp, stood = false;
	entitySpeedX = 70;
}

void Mech::requestAnimation(const AnimationCode* animationRequested, bool forward){
	if(animationRequested->TYPE == "FULL"){
		Entity::setAnimation(animationRequested,false,&fullSelect);
	}
	else{
		Entity::setAnimation(animationRequested,false,&colorSelect);
	}
}

void Mech::render(SDL_Renderer* renderer) {
	if (!isPlayer){
		SDL_RenderCopy(renderer, textureManager.mechTexture, &mechAnim[2][0], &displayRect);
		SDL_RenderCopy(renderer, textureManager.mechTexture, &mechAnim[3][0], &displayRect);
		if (highlighted) {
			SDL_RenderCopy(renderer, textureManager.mechTexture, &mechAnim[1][30], &displayRect);
		}
	}
	else{
		SDL_RenderCopy(renderer,textureManager.mechTexture,&mechAnim[fullSelect.curAnim][fullSelect.curFrame],&displayRect);
		SDL_RenderCopy(renderer,textureManager.mechTexture,&mechAnim[colorSelect.curAnim][colorSelect.curFrame],&displayRect);

	}
			//render grapple
/*			if (grappling) {
				for (int i = handRect[3].x-20; i >= handRect[0].x; i-=28) {
					handRect[2].x = i;
					handRect[2].y = posY + 142;
					SDL_RenderCopy(renderer,textureManager.mechAtTexture,&mechHandArr[2],&handRect[2]);
					
				}
				SDL_RenderCopy(renderer, textureManager.mechAtTexture, &mechHandArr[3], &handRect[3]);
				for (int i = handRect[3].x-8; i >= handRect[0].x;i-=28) {
					handRect[1].x = i;
					handRect[1].y = posY + 144;
				}*/
}

void Mech::moveLeft(bool key) {
	Entity::moveLeft(key);
}

void Mech::moveRight(bool key) {
	Entity::moveRight(key);
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
	
	isHighlighted();
	vector<const AnimationCode*> completedAnims = Entity::updateAnimationFrame();	
	for(auto completedAnim : completedAnims){
		handleCompletedAnimations(completedAnim);
	}
}

void Mech::processCollision(bool collisions[4]) {
	if (collisions[0]) {
		mech.posY = (mech.posY) / mapInfo.TILE_DIM * mapInfo.TILE_DIM;
		mech.velY = 0;
	}
}

void Mech::handleCompletedAnimations(const AnimationCode* animationCompleted){
	if(animationCompleted->TYPE == POWER_UP_COLOR.TYPE && animationCompleted->CODE == POWER_UP_COLOR.CODE){
		Entity::setAnimation(&STAND_UP,false,&fullSelect);
		Entity::setAnimation(&STAND_UP_COLOR,false,&colorSelect);
	}
}
void Mech::isHighlighted(){
	if (abs(camera.cameraTarget->posX - posX - 2 * mapInfo.TILE_DIM) > 80) {
		highlighted = false;
	}
	else {
		highlighted = true;
	}
}