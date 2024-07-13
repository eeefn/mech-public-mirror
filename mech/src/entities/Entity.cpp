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
			animation->curFrame = (animation->curFrame + 1) % (animation->animationCode->MAX_LOOP * ANIM_SPEED);
			animation->playFrame = animation->curFrame / ANIM_SPEED;
			if ((animation->playFrame == (animation->animationCode->MAX_LOOP - 1)) && (animation->loop == false)){
				animation->playFrame = animation->animationCode->MAX_LOOP - 1;
				animation->animCycleComplete = true;
				animation->animSel->curFrame = animation->playFrame;
				if(animation->animationCode->TYPE == "FULL" && animation->animSel->curAnim != 1){
					fullBodyAnimation = false;
				}
			}
			animation->animSel->curFrame = animation->playFrame;
		}
	}
}

void Entity::requestAnimation(const AnimationCode* animationRequested){

}
void Entity::setAnimation(const AnimationCode* animationRequested, bool loop, AnimSelect* animSelect){
	//check for existing instance of animation. 
	if(animationTypesInProgress.find(animationRequested->TYPE) == animationTypesInProgress.end()){
		animSelect->curFrame = 0;
		animSelect->curAnim = animationRequested->CODE;
		AnimationInProgress *newAnimPtr = new AnimationInProgress;
		*newAnimPtr = {animationRequested,animSelect,loop,false,0,0};
		animationsInProgress.push_back(newAnimPtr);
		animationTypesInProgress[animationRequested->TYPE] = 1;
	}
	else{
		//don't override exisiting animation if it is the same animation
		if(animationRequested->CODE != animSelect->curAnim){
			animSelect->curAnim = animationRequested->CODE;
			//update exisiting animation of same type, ie body portion
			for (auto animation : animationsInProgress) {
				if((animationRequested->TYPE == animation->animationCode->TYPE)){
					*animation = {animationRequested, animSelect, loop, false,0,0};
					return;
				}
			}
		}
	}
}

short Entity::getCurrentAnimation(){
	return curAnim;
}