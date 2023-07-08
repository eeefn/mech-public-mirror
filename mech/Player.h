#pragma once
#include "./constants.h"
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



class Player {
public:
	//current animation
	short totalFrame, playFrame;
	short curAnim, curFrame;
	bool inAir;
	bool animCycleComplete;
	int posX, posY;
	int velX, velY;
	float accX, accY;
	int gravity;
	int playerJumpAcc, playerSpeedX;
	Player();
	void updatePlayer(float dt);
	void processCollision(bool collisions[4],SDL_Rect tile[][WINDOW_WIDTH / TILE_DIM]);

};
extern Player player;