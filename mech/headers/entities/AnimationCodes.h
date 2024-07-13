#pragma once
#include <string>
extern struct PlayerAnimationCodes{
    constexpr static short LEGS_MAX_LOOP = 15;
    constexpr static short WALK_L_ANIM = 0;
    constexpr static short IDLE_L_ANIM = 1;
    constexpr static short IDLE_R_ANIM = 2;
    constexpr static short WALK_R_ANIM = 3;
    
    constexpr static short TORSO_MAX_LOOP = 1;
    constexpr static short TORSO_L_ANIM = 1;
    constexpr static short TORSO_R_ANIM = 0;

    constexpr static short HEAD_MAX_LOOP = 2;
    constexpr static short HEAD_L_ANIM = 2;
    constexpr static short HEAD_R_ANIM = 0;
    constexpr static short HEAD_L_FALL_ANIM = 3;
    constexpr static short HEAD_R_FALL_ANIM = 1;
    
    constexpr static short MUSH_GROW_MAX_LOOP = 87;
    constexpr static short MUSH_GROW = 0;
} playerAnimationCodes;

 namespace AnimationType{
    const std::string FULL_SPRITE = "FULL";
    const std::string HEAD = "HEAD";
    const std::string TORSO = "TORSO";
    const std::string LEGS = "LEGS";
}
