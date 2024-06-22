#pragma once
#include <SDL.h>
#define GRAVITY 250
#define ANIM_SPEED 2

extern struct AnimationCodes {
	constexpr static int JUMP_ANIM = 0;
	constexpr static int RUN_R_ANIM = 1;
	constexpr static int IDLE_ANIM = 2;
	constexpr static int RUN_L_ANIM = 3;
}animationCodes;

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

