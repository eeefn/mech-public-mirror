#include "../../headers/entities/Entity.h"
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
	curFrame = (curFrame + 1) % totalFrame;
	playFrame = curFrame / ANIM_SPEED;
	if(playFrame == 14){
		if(!loopCurrentAnimation){
			animCycleComplete = true;
			if(velX < 0){
				setAnimation(animationCodes.RUN_L_ANIM,true);
			}
			else if(velX > 0){
				setAnimation(animationCodes.RUN_R_ANIM,true);
			}
			else{
				setAnimation(animationCodes.IDLE_ANIM,true);
			}
		}
	}	
}

void Entity::setAnimation(int animation,bool loop){
	if(curAnim == animationCodes.JUMP_ANIM && (animation == animationCodes.RUN_L_ANIM || animation == animationCodes.RUN_R_ANIM)){
		if(animCycleComplete){
			loopCurrentAnimation = loop;
			curAnim = animation;
			curFrame = -1;
			animCycleComplete = false;
		}
	}
	else{
		loopCurrentAnimation = loop;
		curAnim = animation;
		curFrame = -1;
		animCycleComplete = false;
	}
}

short Entity::getCurrentAnimation(){
	return curAnim;
}