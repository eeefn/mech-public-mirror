#pragma once
#include "../constants.h"
#include "./Entity.h"
#include <SDL.h>

#define MAX_VEL 200
#define MECH_WIDTH 96 * 2
#define MECH_HEIGHT 144 * 2

class Mech : public Entity 
{
	public:
		bool highlighted;
		Mech();
		bool poweredUp, stood, grappling,reelOut;
		int currFrame,playFrame;
		int gDist = 0;
		void isHighlighted();
		void updateEntity(float dt);
		void moveLeft(bool key);
		void moveRight(bool key);
		void attackRight(int xClick);
		void render(SDL_Renderer* rend);
		void processCollision(bool collisions[4]);
		void requestAnimation(const AnimationCode* animationRequested,bool forward);
		void handleCompletedAnimations(const AnimationCode* animationCompleted);
	protected:
		AnimSelect fullSelect = {0,0};
		AnimSelect colorSelect = {0,0};
		SDL_Rect mechAnim[4][60];
		SDL_Rect handRect[5];
		SDL_Rect mechHandArr[5];
};
extern Mech mech;
