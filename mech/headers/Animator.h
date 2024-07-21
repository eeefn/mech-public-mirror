#pragma once
#include "../headers/entities/AnimationCodes.h"
#include <vector>
#include <unordered_map>
#include <string>

using std::vector;
using std::string;

class Animator{
    public:
        Animator();
        ~Animator();
        struct AnimSelect{
            short curAnim;
            short curFrame;
        };
        short getCurrentAnimation();	
        vector<const AnimationCode*> updateAnimationFrame();
        void setAnimation(const AnimationCode* animationRequested, bool loop, AnimSelect* animSelect, short animSpeed,bool playForward);
        void setAnimation(const AnimationCode* animationRequested, bool loop, AnimSelect* animSelect);
    private:
        struct AnimationInProgress{
            const AnimationCode* animationCode;
            AnimSelect* animSel;
            bool loop;
            bool animCycleComplete;
            short playFrame;
            int curFrame;
            short speed;
            bool forward = true;
        };
        bool allowAnimationOverride(const AnimationCode* animationRequested,AnimationInProgress* curAnimInProgress, AnimSelect* animSelect, bool forward);
        void incrementFrame(AnimationInProgress* animation);
        bool checkAnimationCompletion(AnimationInProgress* animation);
        AnimationInProgress* getCurrentAnimationOfType(string type);
        std::unordered_map<std::string,int> animationTypesInProgress;
        vector<AnimationInProgress*> animationsInProgress;
};