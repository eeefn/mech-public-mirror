#include "../../headers/entities/Entity.h"
#include "stdio.h"
#include <iostream>
#include <math.h>

using std::cout;
void Entity::jump() {
	cout << "called base jump function" << '\n';
}
void Entity::moveLeft(bool key) {

}
void Entity::moveRight(bool key) {

}
void Entity::attackRight(int xClick) {

}
void Entity::render(SDL_Renderer* renderer){
		
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
}
