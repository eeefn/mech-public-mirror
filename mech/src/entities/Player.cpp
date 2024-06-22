
#include <SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include "../../headers/constants.h"
#include "../../headers/entities/Player.h"
#include "../../headers/TextureManager.h"

using std::cout;

Player player;

Player::Player()  {
	//setup rectangles from spritesheet. For now im just initializing 
	//the very first one to get the character moving around
	displayRect.x = 0; displayRect.y = 0;
	displayRect.w = PLAYER_WIDTH; displayRect.h = PLAYER_HEIGHT;
	entityWidth = PLAYER_WIDTH; entityHeight = PLAYER_HEIGHT;
	inAir = true;
	Entity::setAnimation(animationCodes.IDLE_ANIM,false);
	isPlayer = true;
	totalFrame = 15 * ANIM_SPEED;
	posX = WINDOW_WIDTH/2 - PLAYER_WIDTH/2;
	posY = WINDOW_HEIGHT/2 - PLAYER_HEIGHT/2;
	velX = 0; velY = 0;
	accX = 0; accY = GRAVITY;
	entitySpeedX = 100;
	playerJumpAcc = 200;
	soul = 100;
	initializePlayerAnim();
}


void Player::initializePlayerAnim(){	
	//create a grid of rectangles representing the animations from player spritesheet
	for (unsigned int i = 0; i < 15; i++) {
		for (unsigned int j = 0; j < 4; j++) {
			playerAnim[j][i].x = i * 32;
			playerAnim[j][i].y = j*48;
			playerAnim[j][i].w = 32;
			playerAnim[j][i].h = 48;
		}		
	}	
}
void Player::jump() {
	//adjust player velocity to initiate jump
	velY -= playerJumpAcc;
	//change animation to jumping. The reason frame is set to -1 is 
	//player update increments current frame right after this assignment, resulting
	//in the 0th frame being played
	Entity::setAnimation(animationCodes.JUMP_ANIM,false);
	this->inAir = true;
}

void Player::moveLeft(bool key) {
	if (key) {
		velX -= entitySpeedX;
		Entity::setAnimation(animationCodes.RUN_L_ANIM,true);
	}
	else {
		velX += entitySpeedX;
		Entity::setAnimation(animationCodes.IDLE_ANIM,true);
	}
}

void Player::moveRight(bool key) {
	if (key) {
		velX += entitySpeedX;
		Entity::setAnimation(animationCodes.RUN_R_ANIM,true);
	}
	else {
		velX -= entitySpeedX;
		Entity::setAnimation(animationCodes.IDLE_ANIM, true);
	}

}
void Player::render(SDL_Renderer* renderer){
	if (!player.inMech) {
		SDL_RenderCopy(renderer, textureManager.spriteTexture, &playerAnim[Entity::getCurrentAnimation()][player.playFrame], &player.displayRect);
	}
}

void Player::updateEntity(float dt) {
	//updateEntity in the parent does physics
	Entity::updateEntity(dt);
	Entity::updateAnimationFrame();
}


void Player::processCollision(bool collisions[4]) {
	//check y collisions
	if (collisions[0]) {
		//hit ground. This works because of integer division, break the pos into discrete tiles, the re multiply to 
		//get a pos that snaps to grid
		player.posY = (player.posY)/TILE_DIM * TILE_DIM;
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
	}
}