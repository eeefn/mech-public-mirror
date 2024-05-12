#pragma once

#define GRAVITY 250
class Entity
{
public:
	int posX, posY, velX, velY;
	float accY, accX;
	bool isPlayer, inAir;
	int entitySpeedX;
	void updateEntity(float dt);

	virtual void jump();
	virtual void moveLeft(bool key);
	virtual void moveRight(bool key);
	virtual void attackRight(int xClick);
	void processCollision();
	void render();
	
};

