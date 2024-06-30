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
	SDL_Texture* spriteTexture;
	SDL_Rect playerAnim[4][15];
	Player();
	void jump();
	void moveLeft(bool key);
	void moveRight(bool key);
	void updateEntity(float dt);
	void processCollision(bool collisions[4]);
	void render(SDL_Renderer* renderer);
protected:
	void initializePlayerAnim();
};