
#include <SDL.h>
#include <cmath>
#include "../../headers/constants.h"
#include "../../headers/entities/Player.h"
#include "../../headers/entities/AnimationCodes.h"
#include "../../headers/TextureManager.h"
#include "../../headers/Camera.h"
using namespace PlayerAnimationCodes;

#include <iostream>

Player::Player()  {
	displayRect = {0,0,PLAYER_WIDTH,PLAYER_HEIGHT};
	headDisplayRect = {0,0,PLAYER_WIDTH, 20*PLAYER_SCALE};
	torsoDisplayRect = {0,0,PLAYER_WIDTH, 16*PLAYER_SCALE};
	legsDisplayRect = {0,0,PLAYER_WIDTH, 16*PLAYER_SCALE};
	entityWidth = PLAYER_WIDTH; entityHeight = PLAYER_HEIGHT;
	inAir = true;
	isPlayer = true; inMech = false; fullBodyAnimation = false;
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
	for (int i = 0; i < 87; i++) {
		mushGrowAnim[0][i] = {i * 32,0,32,96};
	}
}

void Player::jump() {
	//adjust player velocity to initiate jump
	velY -= playerJumpAcc;
	this->inAir = true;
}

void Player::moveLeft(bool key) {
	if (key) {
		velX -= entitySpeedX;
	}
	else {
		velX += entitySpeedX;
	}
}

void Player::moveRight(bool key) {
	if (key) {
		velX += entitySpeedX;
	}
	else {
		velX -= entitySpeedX;
	}

}
void Player::render(SDL_Renderer* renderer){
	if (!inMech) {
		if (fullBodyAnimation){
			SDL_RenderCopy(renderer, textureManager.mushGrowTexture, &mushGrowAnim[fullSelect.curAnim][fullSelect.curFrame], &displayRect);
		}
		else{
			SDL_RenderCopy(renderer, textureManager.headTexture, &headAnim[headSelect.curAnim][headSelect.curFrame], &headDisplayRect);
			SDL_RenderCopy(renderer,textureManager.torsoTexture,&torsoAnim[torsoSelect.curAnim][torsoSelect.curFrame],&torsoDisplayRect);
			SDL_RenderCopy(renderer, textureManager.legsTexture, &legsAnim[legsSelect.curAnim][legsSelect.curFrame], &legsDisplayRect);
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
		Entity::setAnimation(&WALK_L_ANIM,true,&legsSelect);
		Entity::setAnimation(&TORSO_L_ANIM,true,&torsoSelect);
		setHeadAnimL();
	}
	else if(velX > 0){
		Entity::setAnimation(&WALK_R_ANIM,true,&legsSelect);
		Entity::setAnimation(&TORSO_R_ANIM,true,&torsoSelect);
		setHeadAnimR();
	}
	else{
		if((legsSelect.curAnim == WALK_L_ANIM.CODE) || (legsSelect.curAnim == IDLE_L_ANIM.CODE)){
			Entity::setAnimation(&IDLE_L_ANIM,true,&legsSelect);
			setHeadAnimL();
		}
	  	else{
			Entity::setAnimation(&IDLE_R_ANIM,true,&legsSelect);
			setHeadAnimR();
		}
	}
	Entity::updateAnimationFrame();
}

void Player::setHeadAnimL(){
	if(velY > 50){
		Entity::setAnimation(&HEAD_L_FALL_ANIM,true,&headSelect);
	}
	else{
		Entity::setAnimation(&HEAD_L_ANIM,true,&headSelect);
	}
}

void Player::setHeadAnimR(){
	if(velY > 50){
		Entity::setAnimation(&HEAD_R_FALL_ANIM,true,&headSelect);
	}
	else{
		Entity::setAnimation(&HEAD_R_ANIM,true,&headSelect);
	}
}

void Player::requestAnimation(Entity* requestedBy){
	fullBodyAnimation = true;
	Entity::setAnimation(&MUSH_GROW,false,&fullSelect);
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