#pragma once
#include "../constants.h"
#include "./Entity.h"
#include <SDL.h>
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
protected:
	void initializePlayerAnim();
	short curHeadAnim, curHeadFrame;
	short curTorsoAnim, curTorsoFrame;
	short curLegsAnim, curLegsFrame;
	short curFullAnim;
	SDL_Rect headDisplayRect;
	SDL_Rect torsoDisplayRect;
	SDL_Rect legsDisplayRect;
	SDL_Rect playerAnim[4][15];
	SDL_Rect headAnim[4][3];
	SDL_Rect torsoAnim[2][1];
	SDL_Rect legsAnim[4][15];
};