#pragma once
#include <SDL.h>
#include "../constants.h"
#include "Entity.h"
#include "AnimationCodes.h"
#include "../Animator.h"

#define PLAYER_SCALE 2
#define PLAYER_WIDTH 32*PLAYER_SCALE
#define PLAYER_HEIGHT 48*PLAYER_SCALE
#define MAX_VEL 200



class Player : public Entity{
public:
	//current animation
	bool animCycleComplete;
	int playerJumpAcc, playerSpeedX;
	int soul;
	Player();
	void jump();
	void moveLeft(bool key);
	void moveRight(bool key);
	void updateEntity(float dt);
	void processCollision(bool collisions[4]);
	void render(SDL_Renderer* renderer);
	void requestAnimation(const AnimationCode* animationRequested, bool forward);
	void handleCompletedAnimations(const AnimationCode* animationCompleted);
protected:
	void initializePlayerAnim();
	Animator::AnimSelect headSelect {2,0};
	Animator::AnimSelect torsoSelect {1,0};
	Animator::AnimSelect legsSelect {1,0};
	Animator::AnimSelect fullSelect {0,0};
	SDL_Rect headDisplayRect;
	SDL_Rect torsoDisplayRect;
	SDL_Rect legsDisplayRect;
	SDL_Rect playerAnim[4][15];
	SDL_Rect mushFullAnim[2][87];
	SDL_Rect headAnim[4][3];
	SDL_Rect torsoAnim[2][1];
	SDL_Rect legsAnim[4][15];
private:
	void setHeadAnimR();
	void setHeadAnimL();
};