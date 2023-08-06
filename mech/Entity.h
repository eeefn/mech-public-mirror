#pragma once

#define GRAVITY 250
class Entity
{
public:
	int posX, posY, velX, velY;
	float accY, accX;
	bool isPlayer;
	void updateEntity(float dt);
	void processCollision();
	void render();
	
};

