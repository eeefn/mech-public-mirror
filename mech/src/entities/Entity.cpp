#include "../../headers/entities/Entity.h"
#include "../../headers/entities/AnimationCodes.h"
#include "../../headers/Camera.h"
#include "stdio.h"
#include <iostream>
#include <math.h>

void Entity::jump() {

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
			incrementFrame(animation);
			if (checkAnimationCompletion(animation)){
				if(animation->forward){
					animation->playFrame = animation->animationCode->MAX_LOOP - 1;
				}
				else{
					animation->playFrame = 0;	
				}
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
void Entity::incrementFrame(AnimationInProgress* animation){
	if(animation->forward){
		animation->curFrame = (animation->curFrame + 1) % (animation->animationCode->MAX_LOOP * animation->speed);
		animation->playFrame = animation->curFrame / animation->speed;
	}
	else{
		animation->curFrame = (animation->curFrame - 1) % (animation->animationCode->MAX_LOOP * animation->speed);
		animation->playFrame = animation->curFrame / animation->speed;
	}
}

bool Entity::checkAnimationCompletion(AnimationInProgress* animation){
	if(animation->loop == false){
		if(animation->forward){
			if(animation->playFrame == animation->animationCode->MAX_LOOP - 1){
				return true;
			}
		}
		else{
			if(animation->playFrame == 0){
				return true;
			}
		}	
	}
	return false;
}
void Entity::requestAnimation(const AnimationCode* animationRequested){

}

void Entity::setAnimation(const AnimationCode* animationRequested, bool loop, AnimSelect* animSelect, short animSpeed, bool playForward){
	//check for existing instance of animation. 
	if(animationTypesInProgress.find(animationRequested->TYPE) == animationTypesInProgress.end()){
		animSelect->curAnim = animationRequested->CODE;
		AnimationInProgress *newAnimPtr = new AnimationInProgress;
		if(playForward){
			animSelect->curFrame = 0;
			*newAnimPtr = {animationRequested,animSelect,loop,false,0,0,animSpeed,playForward};
		}
		else{
			short endCurFrame = animationRequested->MAX_LOOP * animSpeed;
			animSelect->curFrame = animationRequested->MAX_LOOP - 1;
			*newAnimPtr = {animationRequested,animSelect,loop,false,animationRequested->MAX_LOOP,endCurFrame,animSpeed,playForward};
		}
		animationsInProgress.push_back(newAnimPtr);
		animationTypesInProgress[animationRequested->TYPE] = 1;
	}
	else{//animation type already exists
		//don't override exisiting animation if it is the same animation
		if(allowAnimationOverride(animationRequested, animSelect, playForward)){
			animSelect->curAnim = animationRequested->CODE;
			//update exisiting animation of same type, ie body portion
			for (auto animation : animationsInProgress) {
				if((animationRequested->TYPE == animation->animationCode->TYPE)){
					if(playForward){
						*animation = {animationRequested, animSelect, loop, false,0,0,animSpeed,playForward};
					}
					else{
						short endCurFrame = animationRequested->MAX_LOOP * animSpeed;
						*animation = {animationRequested, animSelect, loop, false,animationRequested->MAX_LOOP,endCurFrame,animSpeed,playForward};
					}
					return;
				}
			}
		}
	}
	
}
void Entity::setAnimation(const AnimationCode* animationRequested, bool loop, AnimSelect* animSelect){
	setAnimation(animationRequested, loop, animSelect, animationRequested->DEFAULT_SPEED,true);
}


bool Entity::allowAnimationOverride(const AnimationCode* animationRequested, AnimSelect* animSelect, bool forward){
	//animation can be overWritten if the animation is a of the same type, but different animation
	if(animationRequested->CODE != animSelect->curAnim){
		return true;
	}
	//animation can be overWritten if the current animation of the same type is complete 
	//or if the current animation of the same type has a different play direction
	for(auto animation : animationsInProgress){
		if(animation->animationCode->TYPE == animationRequested->TYPE && animation->animCycleComplete){
			if(animation->animCycleComplete){
				return true;
			}
			if(animation->forward != forward){
				return true;
			}
		}
	}

	return false;
}
short Entity::getCurrentAnimation(){
	return curAnim;
}