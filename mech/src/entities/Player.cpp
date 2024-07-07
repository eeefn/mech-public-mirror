
#include <SDL.h>
#include <cmath>
#include "../../headers/constants.h"
#include "../../headers/entities/Player.h"
#include "../../headers/entities/AnimationCodes.h"
#include "../../headers/TextureManager.h"
#include "../../headers/Camera.h"

#include <iostream>

Player::Player()  {
	displayRect = {0,0,PLAYER_WIDTH,PLAYER_HEIGHT};
	headDisplayRect = {0,0,PLAYER_WIDTH, 20*PLAYER_SCALE};
	torsoDisplayRect = {0,0,PLAYER_WIDTH, 16*PLAYER_SCALE};
	legsDisplayRect = {0,0,PLAYER_WIDTH, 16*PLAYER_SCALE};
	
	entityWidth = PLAYER_WIDTH; entityHeight = PLAYER_HEIGHT;
	inAir = true;
	//Entity::setAnimation(animationCodes.IDLE_ANIM,false);
	curHeadAnim = 2; curHeadFrame = 0;
	curTorsoAnim = 0; curTorsoFrame = 0;
	curLegsAnim = 1, curLegsFrame = 0;
	curFullAnim = 0;
	isPlayer = true; inMech = false; fullBodyAnimation = false;
	//totalFrame = 15 * ANIM_SPEED;
	posX = 1280/2 - PLAYER_WIDTH/2;
	posY = 720/2 - PLAYER_HEIGHT/2;
	velX = 0; velY = 0;
	accX = 0; accY = GRAVITY;
	entitySpeedX = 100;
	playerJumpAcc = 200;
	soul = 100;
	initializePlayerAnim();
}


void Player::initializePlayerAnim(){	
	//create a grid of rectangles representing the animations from player spritesheet
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 4; j++) {
			playerAnim[j][i] = {i * 32, j * 48, 32, 48};
		}		
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			headAnim[j][i] = {i * 32, j * 20, 32, 20};
		}
	}
	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 2; j++) {
			torsoAnim[j][i] = {i * 32, j * 16, 32, 16};
		}
	}
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 4; j++) {
			legsAnim[j][i] = {i * 32, j * 16, 32, 16};
		}
	}
}
void Player::jump() {
	//adjust player velocity to initiate jump
	velY -= playerJumpAcc;
	//Entity::setAnimation(animationCodes.JUMP_ANIM,false);
	this->inAir = true;
}

void Player::moveLeft(bool key) {
	if (key) {
		velX -= entitySpeedX;
	//	Entity::setAnimation(animationCodes.RUN_L_ANIM,true);
	}
	else {
		velX += entitySpeedX;
		//Entity::setAnimation(animationCodes.IDLE_ANIM,true);
	}
}

void Player::moveRight(bool key) {
	if (key) {
		velX += entitySpeedX;
//		Entity::setAnimation(animationCodes.RUN_R_ANIM,true);
	}
	else {
		velX -= entitySpeedX;
		//Entity::setAnimation(animationCodes.IDLE_ANIM, true);
	}

}
void Player::render(SDL_Renderer* renderer){
	if (!inMech) {
		if (fullBodyAnimation){
			SDL_RenderCopy(renderer, textureManager.spriteTexture, &playerAnim[Entity::getCurrentAnimation()][curFullAnim], &displayRect);
		}else{
			SDL_RenderCopy(renderer, textureManager.headTexture, &headAnim[curHeadAnim][curHeadFrame], &headDisplayRect);
			SDL_RenderCopy(renderer,textureManager.torsoTexture,&torsoAnim[curTorsoAnim][curTorsoFrame],&torsoDisplayRect);
			SDL_RenderCopy(renderer, textureManager.legsTexture, &legsAnim[curLegsAnim][curLegsFrame], &legsDisplayRect);
		}

	}

}

void Player::updateEntity(float dt) {
	//updateEntity in the parent does physics
	Entity::updateEntity(dt);
	headDisplayRect.x = displayRect.x; headDisplayRect.y = displayRect.y;
	torsoDisplayRect.x = displayRect.x; torsoDisplayRect.y = displayRect.y + 16 * PLAYER_SCALE;
	legsDisplayRect.x = displayRect.x; legsDisplayRect.y = displayRect.y + 32 * PLAYER_SCALE;
	if (velX < 0){
		Entity::setAnimation(playerAnimationCodes.WALK_L_ANIM,true,&curLegsAnim,&curLegsFrame,playerAnimationCodes.LEGS_MAX_LOOP,animationTypes.LEGS_ANIM);
		Entity::setAnimation(playerAnimationCodes.TORSO_L_ANIM,true,&curTorsoAnim,&curTorsoFrame,playerAnimationCodes.TORSO_MAX_LOOP,animationTypes.TORSO_ANIM);
		if(velY > 50){
			Entity::setAnimation(playerAnimationCodes.HEAD_L_FALL_ANIM,true,&curHeadAnim,&curHeadFrame,playerAnimationCodes.HEAD_MAX_LOOP,animationTypes.HEAD_ANIM);
		}
		else{
			Entity::setAnimation(playerAnimationCodes.HEAD_L_ANIM,true,&curHeadAnim,&curHeadFrame,playerAnimationCodes.HEAD_MAX_LOOP,animationTypes.HEAD_ANIM);
		}
	}else if(velX > 0){
		Entity::setAnimation(playerAnimationCodes.WALK_R_ANIM,true,&curLegsAnim,&curLegsFrame,playerAnimationCodes.LEGS_MAX_LOOP,animationTypes.LEGS_ANIM);
		Entity::setAnimation(playerAnimationCodes.TORSO_R_ANIM,true,&curTorsoAnim,&curTorsoFrame,playerAnimationCodes.TORSO_MAX_LOOP,animationTypes.TORSO_ANIM);
		if(velY > 50){
			Entity::setAnimation(playerAnimationCodes.HEAD_R_FALL_ANIM,true,&curHeadAnim,&curHeadFrame,playerAnimationCodes.HEAD_MAX_LOOP,animationTypes.HEAD_ANIM);
		}
		else{
			Entity::setAnimation(playerAnimationCodes.HEAD_R_ANIM,true,&curHeadAnim,&curHeadFrame,playerAnimationCodes.HEAD_MAX_LOOP,animationTypes.HEAD_ANIM);
		}
	}
	else{
		if((curLegsAnim == playerAnimationCodes.WALK_L_ANIM) || (curLegsAnim == playerAnimationCodes.IDLE_L_ANIM)){
			Entity::setAnimation(playerAnimationCodes.IDLE_L_ANIM,true,&curLegsAnim,&curLegsFrame,playerAnimationCodes.LEGS_MAX_LOOP,animationTypes.LEGS_ANIM);
			if(velY > 50){
				Entity::setAnimation(playerAnimationCodes.HEAD_L_FALL_ANIM,true,&curHeadAnim,&curHeadFrame,playerAnimationCodes.HEAD_MAX_LOOP,animationTypes.HEAD_ANIM);
			}
			else{
				Entity::setAnimation(playerAnimationCodes.HEAD_L_ANIM,true,&curHeadAnim,&curHeadFrame,playerAnimationCodes.HEAD_MAX_LOOP,animationTypes.HEAD_ANIM);
			}
		}
	  	else{
			Entity::setAnimation(playerAnimationCodes.IDLE_R_ANIM,true,&curLegsAnim,&curLegsFrame,playerAnimationCodes.LEGS_MAX_LOOP,animationTypes.LEGS_ANIM);
			if(velY > 50){
				Entity::setAnimation(playerAnimationCodes.HEAD_R_FALL_ANIM,true,&curHeadAnim,&curHeadFrame,playerAnimationCodes.HEAD_MAX_LOOP,animationTypes.HEAD_ANIM);
			}
			else{
				Entity::setAnimation(playerAnimationCodes.HEAD_R_ANIM,true,&curHeadAnim,&curHeadFrame,playerAnimationCodes.HEAD_MAX_LOOP,animationTypes.HEAD_ANIM);
			}
		}
	}
	Entity::updateAnimationFrame();
}


void Player::processCollision(bool collisions[4]) {
	//check y collisions
	if (collisions[0]) {
		//hit ground. This works because of integer division, break the pos into discrete tiles, the re multiply to 
		//get a pos that snaps to grid
		posY = (posY)/mapInfo.TILE_DIM * mapInfo.TILE_DIM;
		inAir = false;
		velY = 0;
	}
	else if (collisions[1]) {
		posY = (posY + mapInfo.TILE_DIM - 1) / mapInfo.TILE_DIM * mapInfo.TILE_DIM;
	}
	//check x collsions
	if (collisions[2]) {
		//
		posX = (posX) / mapInfo.TILE_DIM * mapInfo.TILE_DIM;
	}
	else if(collisions[3]){
		//moving left
		posX = ((posX + mapInfo.TILE_DIM - 1) / mapInfo.TILE_DIM) * mapInfo.TILE_DIM;
	}
}