#include "../headers/Animator.h"
#include <iostream>
Animator::Animator(){
    
}

Animator::~Animator(){
    for(auto ptr : animationsInProgress){
        delete ptr;
    }
    animationsInProgress.clear();
}

void Animator::setAnimation(const AnimationCode* animationRequested, bool loop, AnimSelect* animSelect, short animSpeed, bool playForward){
	//check for existing instance of animation. 
	if(animationTypesInProgress.find(animationRequested->TYPE) == animationTypesInProgress.end()){
		animSelect->curAnim = animationRequested->CODE;
		AnimationInProgress *newAnimPtr = new AnimationInProgress;
		if(playForward){
			animSelect->curFrame = 0;
			*newAnimPtr = {animationRequested,animSelect,loop,false,0,0,animSpeed,playForward};
		}
		else{
			short endCurFrame = animationRequested->MAX_LOOP * animSpeed;
			animSelect->curFrame = animationRequested->MAX_LOOP - 1;
			*newAnimPtr = {animationRequested,animSelect,loop,false,animationRequested->MAX_LOOP,endCurFrame,animSpeed,playForward};
		}
		animationsInProgress.push_back(newAnimPtr);
		animationTypesInProgress[animationRequested->TYPE] = 1;
	}
	else{//animation type already exists
		//don't override exisiting animation if it is the same animation
		AnimationInProgress* curAnimInProgress = getCurrentAnimationOfType(animationRequested->TYPE);
		if(allowAnimationOverride(animationRequested, curAnimInProgress, animSelect, playForward)){
			animSelect->curAnim = animationRequested->CODE;
			if(playForward){
				if(curAnimInProgress->forward != playForward){
					*curAnimInProgress = {animationRequested, animSelect, loop, false,curAnimInProgress->playFrame,curAnimInProgress->curFrame,animSpeed,playForward};
				}
				else{
					*curAnimInProgress = {animationRequested, animSelect, loop, false,0,0,animSpeed,playForward};
				}
			}
			else{
				if(curAnimInProgress->forward != playForward){
					*curAnimInProgress = {animationRequested, animSelect, loop, false,curAnimInProgress->playFrame,curAnimInProgress->curFrame,animSpeed,playForward};
				}
				else{
					short endCurFrame = animationRequested->MAX_LOOP * animSpeed;
					*curAnimInProgress = {animationRequested, animSelect, loop, false,animationRequested->MAX_LOOP,endCurFrame,animSpeed,playForward};
				}
			}
		}
	}
}

vector<const AnimationCode*> Animator::updateAnimationFrame(){
	vector<const AnimationCode*> completedAnims;
	for(auto animation : animationsInProgress){
		if(!animation->animCycleComplete){
			incrementFrame(animation);
			if (checkAnimationCompletion(animation)){
				//animation rests on either last or first frame when complete until overwritten
				if(animation->forward){
					animation->playFrame = animation->animationCode->MAX_LOOP - 1;
				}
				else{
					animation->playFrame = 0;	
				}
				animation->animCycleComplete = true;
				animation->animSel->curFrame = animation->playFrame;
				/*if(animation->animationCode->TYPE == "FULL" && animation->animSel->curAnim != 1){
					fullBodyAnimation = false;
				}*/
				completedAnims.push_back(animation->animationCode);
			}
			animation->animSel->curFrame = animation->playFrame;
		}
	}
	return completedAnims;
}

void Animator::incrementFrame(AnimationInProgress* animation){
	if(animation->forward){
		animation->curFrame = (animation->curFrame + 1) % (animation->animationCode->MAX_LOOP * animation->speed);
		animation->playFrame = animation->curFrame / animation->speed;
	}
	else{
		animation->curFrame = (animation->curFrame - 1) % (animation->animationCode->MAX_LOOP * animation->speed);
		animation->playFrame = animation->curFrame / animation->speed;
	}
}

bool Animator::checkAnimationCompletion(AnimationInProgress* animation){
	if(animation->loop == false){
		if(animation->forward){
			if(animation->playFrame == animation->animationCode->MAX_LOOP - 1){
				return true;
			}
		}
		else{
			if(animation->playFrame == 0){
				return true;
			}
		}	
	}
	return false;
}

void Animator::setAnimation(const AnimationCode* animationRequested, bool loop, AnimSelect* animSelect){
	setAnimation(animationRequested, loop, animSelect, animationRequested->DEFAULT_SPEED,true);
}

Animator::AnimationInProgress* Animator::getCurrentAnimationOfType(string type){
	for(auto animation : animationsInProgress){
		if(animation->animationCode->TYPE == type){
			return animation;
		}
	}
	return nullptr;
}

bool Animator::allowAnimationOverride(const AnimationCode* animationRequested, AnimationInProgress* curAnimInProgress, AnimSelect* animSelect, bool forward){
	//animation can be overWritten if the animation is a of the same type, but different animation
	//animation can be overWritten if the current animation of the same type is complete 
	//or if the current animation of the same type has a different play direction
	if(curAnimInProgress->animationCode->blocking && !curAnimInProgress->animCycleComplete){
		return false;
	}
	if(animationRequested->CODE != animSelect->curAnim){
		return true;
	}
	if(curAnimInProgress->animCycleComplete){
		return true;
	}
	if(curAnimInProgress->forward != forward && curAnimInProgress->animationCode->CODE == animationRequested->CODE){
		return true;
	}
	return false;
}