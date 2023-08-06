#include "Entity.h"
#include "stdio.h"
#include <iostream>

using std::cout;

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
