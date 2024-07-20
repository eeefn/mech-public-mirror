#pragma once
#include <SDL.h>
#include "AnimationCodes.h"
#include "../Animator.h"

#define GRAVITY 250
#define ANIM_SPEED 2
using std::vector;
using std::string;

class Entity
{
	public:
		Entity* hostEntity;
		int entityWidth, entityHeight;
		int posX, posY, velX, velY;
		float accY, accX;
		bool isPlayer, inAir, entityTransition, inMech, fullBodyAnimation;
		int entitySpeedX, entitySpeedY = 0;
		SDL_Rect displayRect;
		void stop();
		virtual void updateEntity(float dt);
		virtual void jump();
		virtual void moveLeft(bool key);
		virtual void moveRight(bool key);
		virtual void moveUp(bool key);
		virtual void moveDown(bool key);
		virtual void attackRight(int xClick);
		virtual void render(SDL_Renderer* renderer);	
		virtual void processCollision(bool collisions[4]);
		virtual void requestAnimation(const AnimationCode* animationRequested,bool forward);
		virtual void handleCompletedAnimations(const AnimationCode* animationCompleted);
		virtual ~Entity();
	protected:
		Animator animator{};
};

