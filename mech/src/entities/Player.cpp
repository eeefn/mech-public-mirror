#include <SDL.h>
#include <cmath>

#include "../../headers/constants.h"
#include "../../headers/entities/Player.h"
#include "../../headers/entities/AnimationCodes.h"
#include "../../headers/TextureManager.h"
#include "../../headers/Camera.h"
#include "../../headers/PlayerState.h"

using namespace PlayerAnimationCodes;

Player::Player()  {
	identifier = "PLAYER";
	displayRect = {0,0,PLAYER_WIDTH,PLAYER_HEIGHT};
	headDisplayRect = {0,0,PLAYER_WIDTH, 20*PLAYER_SCALE};
	torsoDisplayRect = {0,0,PLAYER_WIDTH, 16*PLAYER_SCALE};
	legsDisplayRect = {0,0,PLAYER_WIDTH, 16*PLAYER_SCALE};
	swingDisplayRect = {0,0,32*PLAYER_SCALE,48*PLAYER_SCALE};
	posOnSwingTexture = {0,0,32,48};
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
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			torsoAnim[j][i] = {i * 32, j * 16, 32, 16};
		}
	}
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 4; j++) {
			legsAnim[j][i] = {i * 32, j * 16, 32, 16};
		}
	}
	for (int i = 0; i < 87; i++) {
		for(int j = 0; j < 2; j++){
			mushFullAnim[j][i] = {i * 32,j * 48,32,48};
		}
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
			SDL_RenderCopy(renderer, textureManager.mushFullTexture, &mushFullAnim[fullSelect.curAnim][fullSelect.curFrame], &displayRect);
		}
		else{
			SDL_RenderCopy(renderer, textureManager.headTexture, &headAnim[headSelect.curAnim][headSelect.curFrame], &headDisplayRect);
			SDL_RenderCopy(renderer,textureManager.torsoTexture,&torsoAnim[torsoSelect.curAnim][torsoSelect.curFrame],&torsoDisplayRect);
			SDL_RenderCopy(renderer, textureManager.legsTexture, &legsAnim[legsSelect.curAnim][legsSelect.curFrame], &legsDisplayRect);
			if((torsoSelect.curAnim == 3 || torsoSelect.curAnim == 2) && checkAndSetValidTool()){
				updateTextRectToolSwing();
				if(!facingL){
					SDL_RenderCopy(renderer,textureManager.toolSwingTexture,&posOnSwingTexture,&swingDisplayRect);
				}
				else{
					swingDisplayRect.x -= (PLAYER_WIDTH - 4*PLAYER_SCALE);
					SDL_RenderCopyEx(renderer,textureManager.toolSwingTexture,&posOnSwingTexture,&swingDisplayRect,0,NULL,SDL_RendererFlip::SDL_FLIP_HORIZONTAL);
				}
			}
		}
	}
}

void Player::updateEntity(float dt) {
	//updateEntity in the parent does physics
	Entity::updateEntity(dt);
	headDisplayRect.x = displayRect.x; headDisplayRect.y = displayRect.y;
	torsoDisplayRect.x = displayRect.x; torsoDisplayRect.y = displayRect.y + 16 * PLAYER_SCALE;
	legsDisplayRect.x = displayRect.x; legsDisplayRect.y = displayRect.y + 32 * PLAYER_SCALE;
	swingDisplayRect.x = displayRect.x + 14 * PLAYER_SCALE; swingDisplayRect.y = displayRect.y;
	if (velX < 0){
		animator.setAnimation(&WALK_L_ANIM,true,&legsSelect);
		animator.setAnimation(&TORSO_L_ANIM,true,&torsoSelect);
		facingL = true;
		setHeadAnimL();
	}
	else if(velX > 0){
		animator.setAnimation(&WALK_R_ANIM,true,&legsSelect);
		animator.setAnimation(&TORSO_R_ANIM,true,&torsoSelect);
		facingL = false;
		setHeadAnimR();
	}
	else{
		if((legsSelect.curAnim == WALK_L_ANIM.CODE) || (legsSelect.curAnim == IDLE_L_ANIM.CODE)){
			animator.setAnimation(&IDLE_L_ANIM,true,&legsSelect);
			facingL = true;
			setHeadAnimL();
		}
	  	else{
			animator.setAnimation(&IDLE_R_ANIM,true,&legsSelect);
			facingL = false;
			setHeadAnimR();
		}
	}
	vector<const AnimationCode*> completedAnims = animator.updateAnimationFrame();
	for(auto completedAnim : completedAnims){
		handleCompletedAnimations(completedAnim);
	}
}

void Player::setHeadAnimL(){
	if(velY > 50){
		animator.setAnimation(&HEAD_L_FALL_ANIM,true,&headSelect);
	}
	else{
		animator.setAnimation(&HEAD_L_ANIM,true,&headSelect);
	}
}

void Player::setHeadAnimR(){
	if(velY > 50){
		animator.setAnimation(&HEAD_R_FALL_ANIM,true,&headSelect);
	}
	else{
		animator.setAnimation(&HEAD_R_ANIM,true,&headSelect);
	}
}

void Player::requestAnimation(const AnimationCode* animationRequested, bool forward){
	if(animationRequested->TYPE == "FULL"){
		fullBodyAnimation = true;
		animator.setAnimation(animationRequested,false,&fullSelect,2,forward);
		if(animationRequested->CODE == MUSH_GROW.CODE){
			animator.setAnimation(&HEAD_R_ANIM,true,&headSelect,2,forward);
			animator.setAnimation(&IDLE_R_ANIM,true,&legsSelect,2,forward);	
			animator.setAnimation(&TORSO_R_ANIM,true,&torsoSelect,2,forward);
		}
	}
	else{
		if(animationRequested->TYPE == "TORSO"){
			animator.setAnimation(animationRequested,false,&torsoSelect,animationRequested->DEFAULT_SPEED,forward);
		}
	}
}

void Player::handleCompletedAnimations(const AnimationCode* animationCompleted){
	if(animationCompleted->TYPE == MUSH_KNEEL.TYPE && animationCompleted->CODE == MUSH_KNEEL.CODE){
		if(fullSelect.curFrame == 0){
			fullBodyAnimation = false;
		}
	}
	if(animationCompleted->TYPE == MUSH_GROW.TYPE && animationCompleted->CODE == MUSH_GROW.CODE){
		fullBodyAnimation = false;
	}
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

void Player::updateTextRectToolSwing(){
	int soulColor = playerState.getSoulColor();
	posOnSwingTexture.x = (soulColor * (5*32)) + (torsoSelect.curFrame * 32);
	posOnSwingTexture.y = (heldToolCode - 2) * 48;
}

bool Player::checkAndSetValidTool(){
	Item* heldItem = playerState.hotbar.getItemAtSelectedSlot();
	int itemCode = heldItem->itemType;
	if(itemCode == 2 || itemCode == 3 || itemCode == 4){
		heldToolCode = itemCode;
		return true;
	}
	return false;
}