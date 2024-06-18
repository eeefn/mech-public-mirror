#pragma once
#include <SDL.h>
#define GRAVITY 250
#define IDLE_ANIM 2
#define JUMP_ANIM 0
#define RUN_R_ANIM 1
#define UPAIR_ANIM 0
#define RUN_L_ANIM 3
#define ANIM_SPEED 2

class Entity
{
public:
	int entityWidth, entityHeight;
	short totalFrame, playFrame;
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
	virtual void processCollision(bool collisions[4]);
protected:
	short getCurrentAnimation();	
	void updateAnimationFrame();
	void setAnimation(int animation, bool loop);
private:
	bool animCycleComplete = false; bool loopCurrentAnimation;
	short curAnim, curFrame = 0; 
};

