#pragma once
#include <SDL.h>
#include <vector>
#include <unordered_map>
#include <string>

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
	virtual void requestAnimation(Entity* requestedBy);
	virtual ~Entity();
protected:
	struct AnimSelect{
		short curAnim;
		short curFrame;
	};
	short getCurrentAnimation();	
	void updateAnimationFrame();
	void setAnimation(short animationRequested, bool loop, AnimSelect* animSelect, short maxFrames,string animationType);
private:
	short curAnim = 0;
	struct AnimationInProgress{
		bool loop;
		short maxFrames;
		short playFrame;
		bool animCycleComplete;
		string animationType;
		int curFrame;
		AnimSelect* animSel;
	};
	std::unordered_map<std::string,int> animationTypesInProgress;
	vector<AnimationInProgress*> animationsInProgress;
};

