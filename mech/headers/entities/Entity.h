#pragma once
#include <SDL.h>
#include <vector>
#include <unordered_map>
#include <string>
#include "AnimationCodes.h"

#define GRAVITY 250
#define ANIM_SPEED 2
using std::vector;
using std::string;

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
	virtual void requestAnimation(const AnimationCode* animationRequested);
	virtual ~Entity();
protected:
	struct AnimSelect{
		short curAnim;
		short curFrame;
	};
	short getCurrentAnimation();	
	void updateAnimationFrame();
	void setAnimation(const AnimationCode* animationRequested, bool loop, AnimSelect* animSelect, short animSpeed);
	void setAnimation(const AnimationCode* animationRequested, bool loop, AnimSelect* animSelect);
private:
	short curAnim = 0;
	struct AnimationInProgress{
		const AnimationCode* animationCode;
		AnimSelect* animSel;
		bool loop;
		bool animCycleComplete;
		short playFrame;
		int curFrame;
		short speed;
		bool forward = true;
	};
	void incrementFrame(AnimationInProgress* animation);
	bool checkAnimationCompletion(AnimationInProgress* animation);
	std::unordered_map<std::string,int> animationTypesInProgress;
	vector<AnimationInProgress*> animationsInProgress;
};

