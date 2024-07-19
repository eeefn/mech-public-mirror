#pragma once
#include <string>

struct AnimationCode{
    std::string TYPE;
    short CODE;
    short MAX_LOOP;
};

namespace PlayerAnimationCodes{
    const AnimationCode WALK_L_ANIM{"LEGS",0,15};
    const AnimationCode IDLE_L_ANIM{"LEGS",1,15};
    const AnimationCode IDLE_R_ANIM{"LEGS",2,15};
    const AnimationCode WALK_R_ANIM{"LEGS",3,15};

    const AnimationCode TORSO_L_ANIM{"TORSO",1,1};
    const AnimationCode TORSO_R_ANIM{"TORSO",0,1};

    const AnimationCode HEAD_R_ANIM{"HEAD",0,2};
    const AnimationCode HEAD_R_FALL_ANIM{"HEAD",1,2};
    const AnimationCode HEAD_L_ANIM{"HEAD",2,2};
    const AnimationCode HEAD_L_FALL_ANIM{"HEAD",1,3};
    
    const AnimationCode MUSH_GROW{"FULL",0,87};
    const AnimationCode MUSH_KNEEL{"FULL",1,11};
}

namespace MechAnimationCodes{
   const AnimationCode STAND_UP{"FULL",0,30};
   const AnimationCode POWER_UP{"FULL",2,59};
   const AnimationCode STAND_UP_COLOR{"COLOR",1,30};
   const AnimationCode POWER_UP_COLOR{"COLOR",3,59};
}

