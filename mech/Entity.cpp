#include "Entity.h"
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
void Entity::updateEntity(float dt) {
	//cout << "hello from entity :)" << '\n';
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
