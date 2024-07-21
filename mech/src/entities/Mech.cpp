#include "../../headers/entities/Mech.h"
#include "../../headers/Camera.h"
#include "../../headers/TextureManager.h"
#include "../../headers/entities/AnimationCodes.h"

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
	posX = 400; posY = 80;
	isPlayer, inAir, entityTransition = false;
	velX, velY = 0;
	accX = 0; accY = GRAVITY;
	highlighted = true;
	poweredUp, stood = false;
	entitySpeedX = 70;
}

void Mech::requestAnimation(const AnimationCode* animationRequested, bool forward){
	if(animationRequested->TYPE == "FULL"){
		animator.setAnimation(animationRequested,false,&fullSelect);
	}
	else{
		animator.setAnimation(animationRequested,false,&colorSelect);
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
}

void Mech::moveLeft(bool key) {
	Entity::moveLeft(key);
}

void Mech::moveRight(bool key) {
	Entity::moveRight(key);
}

void Mech::attackRight(int xClick) {
}

void Mech::updateEntity(float dt) {
	Entity::updateEntity(dt);
	isHighlighted();
	vector<const AnimationCode*> completedAnims = animator.updateAnimationFrame();	
	for(auto completedAnim : completedAnims){
		handleCompletedAnimations(completedAnim);
	}
}

void Mech::processCollision(bool collisions[4]) {
	if (collisions[0]) {
		posY = (posY) / mapInfo.TILE_DIM * mapInfo.TILE_DIM;
		velY = 0;
	}
}

void Mech::handleCompletedAnimations(const AnimationCode* animationCompleted){
	//trigger stand up after power on animations complete
	if(animationCompleted->TYPE == POWER_UP_COLOR.TYPE && animationCompleted->CODE == POWER_UP_COLOR.CODE){
		animator.setAnimation(&STAND_UP,false,&fullSelect);
		animator.setAnimation(&STAND_UP_COLOR,false,&colorSelect);
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