#pragma once
#include <SDL.h>
#include <vector>
#define GRAVITY 250
#define ANIM_SPEED 2
using std::vector;
extern struct AnimationCodes {
	constexpr static int JUMP_ANIM = 0;
	constexpr static int RUN_R_ANIM = 1;
	constexpr static int IDLE_ANIM = 2;
	constexpr static int RUN_L_ANIM = 3;
}animationCodes;

class Entity
{
public:
	Entity* hostEntity;
	int entityWidth, entityHeight;
	int posX, posY, velX, velY;
	float accY, accX;
	bool isPlayer, inAir, entityTransition, inMech, fullBodyAnimation;
	int entitySpeedX, entitySpeedY = 0;
	SDL_Rect displayRect;
	void stop();
	virtual void updateEntity(float dt);
	virtual void jump();
	virtual void moveLeft(bool key);
	virtual void moveRight(bool key);
	virtual void moveUp(bool key);
	virtual void moveDown(bool key);
	virtual void attackRight(int xClick);
	virtual void render(SDL_Renderer* renderer);	
	virtual void processCollision(bool collisions[4]);
	virtual ~Entity();
protected:
	short getCurrentAnimation();	
	void updateAnimationFrame();
	void setAnimation(short animationRequested, bool loop, short* currentAnimation, short* playFrame, short maxFrames,short animationType);
private:
	short curAnim = 0;
	struct AnimationInProgress{
		bool loop;
		short maxFrames;
		short* playFrame;
		bool animCycleComplete;
		short animationType;
		int curFrame;
	};
	vector<AnimationInProgress*> animationsInProgress;
};

