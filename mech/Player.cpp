#pragma once
#include "./Player.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include "./constants.h"
#include <SDL.h>

using std::cout;

Player player;

Player::Player() {
	//setup rectangles from spritesheet. For now im just initializing 
	//the very first one to get the character moving around
	inAir = true;
	animCycleComplete = false;
	curAnim = IDLE_ANIM;
	//
	totalFrame = 15 * ANIM_SPEED;
	playFrame = 0;
	//currFrame = 0;
	//
	curFrame = 0;
	posX = 0;
	posY = 0;
	velX = 0;
	velY = 0;
	accX = 0;
	gravity = 200;
	//this is gravity. im pretty sure this should never be modified. still fuzzy tho
	accY = gravity;
	playerSpeedX = 100;
	playerJumpAcc = 200;
}

void Player::updatePlayer(float dt) {
	//lets do physics. velocity is updated by acceleration * delta time
	//cout << "accy is " << accY << '\n';
	if (this->accY > gravity) {
		this->accY = gravity;
	}
	this->velY += this->accY * dt;
	//Position is updated by velocity and delta time
	this->posX += round(this->velX * dt); 
	this->posY += round(this->velY * dt);
	//i think this should be moved to a collision method within some other class
	if (this->posX < 0) {
		posX = 0;
	}
	if (this->posY < 0) {
		posY = 0;
	}
	if (!(animCycleComplete && curAnim == JUMP_ANIM)) {
		curFrame = (curFrame + 1) % totalFrame;
		playFrame = curFrame / ANIM_SPEED;
		//cout << "currFrame is " << currFrame << '\n';
		//cout << "playframe is " << playFrame << '\n';
		//curFrame = (curFrame + 1) % 15;
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


void Player::processCollision(bool collisions[4],SDL_Rect tile[][WINDOW_WIDTH / TILE_DIM]){
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