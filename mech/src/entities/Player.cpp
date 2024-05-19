
#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include "../../headers/constants.h"
#include "../../headers/entities/Player.h"


using std::cout;

Player player;

Player::Player()  {
	//setup rectangles from spritesheet. For now im just initializing 
	//the very first one to get the character moving around
	displayRect.x = 0;
	displayRect.y = 0;
	displayRect.w = PLAYER_WIDTH;
	displayRect.h = PLAYER_HEIGHT;
	entityWidth = PLAYER_WIDTH;
	entityHeight = PLAYER_HEIGHT;
	inAir = true;
	animCycleComplete = false;
	curAnim = IDLE_ANIM;
	isPlayer = true;
	totalFrame = 15 * ANIM_SPEED;
	playFrame = 0;
	//currFrame = 0;
	curFrame = 0;
	posX = WINDOW_WIDTH/2 - PLAYER_WIDTH/2;
	posY = WINDOW_HEIGHT/2 - PLAYER_HEIGHT/2;
	velX = 0;
	velY = 0;
	accX = 0;
	accY = GRAVITY;
	entitySpeedX = 100;
	playerJumpAcc = 200;
	soul = 100;
	entityWidth = PLAYER_WIDTH;
	entityHeight = PLAYER_HEIGHT;
}

void Player::jump() {
	//adjust player velocity to initiate jump
	velY -= playerJumpAcc;
	//change animation to jumping. The reason frame is set to -1 is 
	//player update increments current frame right after this assignment, resulting
	//in the 0th frame being played
	curAnim = JUMP_ANIM;
	playFrame = -1;
	this->inAir = true;
}

void Player::moveLeft(bool key) {
	if (key) {
		velX -= entitySpeedX;
		curAnim = RUN_L_ANIM;
		playFrame = -1;
	}
	else {
		velX += entitySpeedX;
		curAnim = IDLE_ANIM;
		playFrame = -1;
	}
}
void Player::moveRight(bool key) {
	if (key) {
		velX += entitySpeedX;
		curAnim = RUN_R_ANIM;
		playFrame = -1;
	}
	else {
		velX -= entitySpeedX;
		curAnim = IDLE_ANIM;
		playFrame = -1;
	}

}
void Player::updateEntity(float dt) {
	//updateEntity in the parent does physics
	Entity::updateEntity(dt);
	//i think this should be moved to a collision method within some other class
	if (posX < 0) {
		posX = 0;
	}
	if (posY < 0) {
		posY = 0;
	}
	if (!(animCycleComplete && curAnim == JUMP_ANIM)) {
		curFrame = (curFrame + 1) % totalFrame;
		playFrame = curFrame / ANIM_SPEED;
	}
	if (playFrame == 14) {
		animCycleComplete = true;
		//cout << "anim Cycle true" << '\n';
	}
	else if (playFrame == 0) {
		animCycleComplete = false;
	}
	if (player.inAir && (velY < 0) && player.animCycleComplete) {
		//cout << "this happened" << '\n';
			curAnim = JUMP_ANIM;
			playFrame = 14;
	}
	else if (player.inAir && (velY > 0)) {
		curAnim = JUMP_ANIM;
		playFrame = 8;
	}
	else if ((player.velX > 0) && !player.inAir) {
		curAnim = RUN_R_ANIM;
	}
	else if ((player.velX < 0) && !player.inAir) {
		curAnim = RUN_L_ANIM;
	}
}


void Player::processCollision(bool collisions[4]) {
	//check y collisions
	if (collisions[0]) {
		//hit ground. This works because of integer division, break the pos into discrete tiles, the re multiply to 
		//get a pos that snaps to grid
		player.posY = (player.posY)/TILE_DIM * TILE_DIM;
		if (player.inAir) {
			player.curAnim = IDLE_ANIM;
			player.playFrame = -1;
		}
		player.inAir = false;
		player.velY = 0;
	}
	else if (collisions[1]) {
		player.posY = (player.posY + TILE_DIM - 1) / TILE_DIM * TILE_DIM;
	}
	//check x collsions
	if (collisions[2]) {
		//
		player.posX = (player.posX) / TILE_DIM * TILE_DIM;
	}
	else if(collisions[3]){
		//moving left
		player.posX = ((player.posX + TILE_DIM - 1) / TILE_DIM) * TILE_DIM;
		//player.posX = ((player.posX + TILE_DIM - 1) / TILE_DIM) * TILE_DIM;
	}
}