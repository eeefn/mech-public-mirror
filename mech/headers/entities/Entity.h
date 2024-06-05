#pragma once
#include <SDL.h>
#define GRAVITY 250
class Entity
{
public:
	int entityWidth, entityHeight;
	int posX, posY, velX, velY;
	float accY, accX;
	bool isPlayer, inAir, entityTransition;
	int entitySpeedX;
	SDL_Rect displayRect;
	void stop();
	virtual void updateEntity(float dt);
	virtual void jump();
	virtual void moveLeft(bool key);
	virtual void moveRight(bool key);
	virtual void attackRight(int xClick);
	virtual void render(SDL_Renderer* renderer);	
	void processCollision();
	
};

