#pragma once
#include "./Player.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include "./constants.h"
using std::cout;
Player player;

Player::Player() {
	//setup rectangles from spritesheet. For now im just initializing 
	//the very first one to get the character moving around
	posX = 100;
	posY = 100;
	velX = 0;
	velY = 0;
	accX = 0;
	fric = 5;
	//this is gravity. im pretty sure this should never be modified. still fuzzy tho
	accY = 0;
	playerSpeed = 50;
}

void Player::updatePlayer(float dt) {
	if (this->accX > 0) {
		this->accX = this->accX - this->fric;
	}
	//lets do physics. velocity is updated by acceleration * delta time
	//this->velX += this->accX * dt;
	//Position is updated by velocity and delta time
	cout << "vel*dt " << this->velX * dt << '\n';
	this->posX += round(this->velX * dt); 
	this->posY += round(this->velY * dt);
	if (this->posX < 0) {
		posX = 0;
	}
	if (this->posY < 0) {
		posY = 0;
	}
	//location of foot
	int collision = (this->posY + 48*2)/ TILE_DIM;
	


}