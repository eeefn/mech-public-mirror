#include "../../headers/entities/Entity.h"
#include "../../headers/entities/AnimationCodes.h"
#include "../../headers/Camera.h"
#include "stdio.h"
#include <iostream>
#include <math.h>

using std::cout;
void Entity::jump() {
	cout << "called base jump function" << '\n';
}
void Entity::moveLeft(bool key) {
	if(key){
		velX -= entitySpeedX;
	}
	else{
		velX += entitySpeedX;
	}
}
void Entity::moveRight(bool key) {
	if (key) {
		velX += entitySpeedX;
	}
	else {
		velX -= entitySpeedX;
	}
}
void Entity::attackRight(int xClick) {

}
void Entity::moveUp(bool key){
	if (key) {
		velY -= entitySpeedY;
	}
	else{
		velY += entitySpeedY;
	}
}

void Entity::moveDown(bool key){
	if (key) {
		velY += entitySpeedY;
	}
	else{
		velY -= entitySpeedY;
	}
}
void Entity::render(SDL_Renderer* renderer){
		
}
Entity::~Entity(){

}
void Entity::stop(){
	velX = 0;
}
void Entity::processCollision(bool collisions[4]){
	
}

void Entity::updateEntity(float dt) {
	if (accY > GRAVITY) {
		accY = GRAVITY;
	}
	velY += accY * dt;
	if (velY >= 200) {
		velY = 200;
	}
	posX += round(velX * dt);
	posY += round(velY * dt);

	displayRect.x = camera.getXPosWithinFrame(posX);
	displayRect.y = camera.getYPosWithinFrame(posY);
}

void Entity::updateAnimationFrame(){
	for(auto animation : animationsInProgress){
		if(!animation->animCycleComplete){
			animation->curFrame = (animation->curFrame + 1) % (animation->maxFrames * ANIM_SPEED);
			*animation->playFrame = animation->curFrame / ANIM_SPEED;
			if ((*animation->playFrame == (animation->maxFrames - 1)) && (animation->loop == false)){
				*animation->playFrame = 0;
				animation->animCycleComplete = true;
				//mark animation for deletion
			}
		}
	}
}

void Entity::setAnimation(short animationRequested, bool loop, AnimSelect* animSelect, short maxFrames,short animationType){
	if((animationRequested != animSelect->curAnim) || (!loop)){
		animSelect->curAnim = animationRequested;
		//update exisiting animation of same type
		for (auto animation : animationsInProgress) {
			if((animationType == animation->animationType)){
				*animation = {loop, maxFrames, &animSelect->curFrame, false,animationType,0};
				return;
			}
		}
		animSelect->curFrame = 0;
		AnimationInProgress *newAnimPtr = new AnimationInProgress;
		*newAnimPtr = {loop,maxFrames, &animSelect->curFrame, false,animationType,0};
		animationsInProgress.push_back(newAnimPtr);
	}
}

short Entity::getCurrentAnimation(){
	return curAnim;
}