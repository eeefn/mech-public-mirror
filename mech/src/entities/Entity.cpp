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


void Entity::requestAnimation(const AnimationCode* animationRequested,bool forward){

}
void Entity::handleCompletedAnimations(const AnimationCode* animationCompleted){

}