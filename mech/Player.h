#pragma once

class Player {
public:
	//heres a structure to store the rectangles that populate the spritesheet
	//i think this should get populated during the construction

	int posX;
	int posY;
	int velX, velY;
	float accX, accY;
	float fric;
	int playerSpeed;
	Player();
	void updatePlayer(float dt);

	
};
extern Player player;