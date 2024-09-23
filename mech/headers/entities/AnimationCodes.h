#pragma once
#include <string>

struct AnimationCode{
    std::string TYPE;
    short CODE;
    short MAX_LOOP;
    short DEFAULT_SPEED = 2;
    bool blocking;
};

namespace PlayerAnimationCodes{
    const AnimationCode WALK_L_ANIM{"LEGS",0,15,2,false};
    const AnimationCode IDLE_L_ANIM{"LEGS",1,15,2,false};
    const AnimationCode IDLE_R_ANIM{"LEGS",2,15,2,false};
    const AnimationCode WALK_R_ANIM{"LEGS",3,15,2,false};

    const AnimationCode TORSO_R_ANIM{"TORSO",0,1,2,false};
    const AnimationCode TORSO_L_ANIM{"TORSO",1,1,2,false};
    const AnimationCode TORSO_SWING_R{"TORSO",3,5,6,true};
    const AnimationCode TORSO_SWING_L{"TORSO",2,5,6,true};

    const AnimationCode HEAD_R_ANIM{"HEAD",0,2,2,false};
    const AnimationCode HEAD_R_FALL_ANIM{"HEAD",1,2,2,false};
    const AnimationCode HEAD_L_ANIM{"HEAD",2,2,2,false};
    const AnimationCode HEAD_L_FALL_ANIM{"HEAD",3,3,2,false};
    
    const AnimationCode MUSH_GROW{"FULL",0,87,2,true};
    const AnimationCode MUSH_KNEEL{"FULL",1,11,2,false};
}

namespace MechAnimationCodes{
   const AnimationCode STAND_UP{"FULL",0,30,4,true};
   const AnimationCode STAND_UP_COLOR{"COLOR",1,30,4,false};
   const AnimationCode POWER_UP{"FULL",2,59,4,true};
   const AnimationCode POWER_UP_COLOR{"COLOR",3,59,4,false};
}

namespace PortalAnimationCodes{
   const AnimationCode MOVE_DISCS{"FULL",0,26,true};
   const AnimationCode OPEN_PORTAL_G{"COLOR",1,55,2,true};
}

