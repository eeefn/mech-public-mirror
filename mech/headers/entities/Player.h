#pragma once
#include "../constants.h"
#include "./Entity.h"
#include <SDL.h>
#define IDLE_ANIM 2
#define JUMP_ANIM 0
#define RUN_R_ANIM 1
#define UPAIR_ANIM 0
#define RUN_L_ANIM 3
#define PLAYER_SCALE 2
#define ANIM_SPEED 2
#define PLAYER_WIDTH 32*PLAYER_SCALE
#define PLAYER_HEIGHT 48*PLAYER_SCALE
#define MAX_VEL 200



class Player : public Entity{
public:
	//current animation
	short totalFrame, playFrame;
	short curAnim, curFrame;
	bool animCycleComplete;
	int playerJumpAcc, playerSpeedX;
	int soul;
	bool inMech = false;
	SDL_Texture* spriteTexture;
	SDL_Rect playerAnim[4][15];
	Player();
	void jump();
	void moveLeft(bool key);
	void moveRight(bool key);
	void updateEntity(float dt);
	void processCollision(bool collisions[4]);
	void render(SDL_Renderer* renderer);
	void initializeSpriteTexture(SDL_Renderer* renderer);
private:
	void initializePlayerAnim();
};
extern Player player;