#include "../../headers/gameObjects/Portal.h"
#include "../../headers/TextureManager.h"

using namespace PortalAnimationCodes;

Portal::Portal(short id,int xT,int yT) : GameObject(3,96,72){
    objectTexture = textureManager.portalTexture;
    ID = id;
    xTile = xT;
    yTile = yT;
    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 55;j++){
            portalAnimRect[i][j] = {j*96,i*72,96,72};
        }
    }
}

void Portal::render(SDL_Renderer* rend){
    SDL_RenderCopy(rend,objectTexture,&portalAnimRect[discs.curAnim][discs.curFrame],&renderRects.posOnScreen);
    SDL_RenderCopy(rend,objectTexture,&portalAnimRect[beam.curAnim][beam.curFrame],&renderRects.posOnScreen);
    SDL_RenderCopy(rend,objectTexture,&portalAnimRect[1][0],&renderRects.posOnScreen);
}

bool Portal::activate(){
    if(!active){
        anim.setAnimation(&MOVE_DISCS,false,&discs,4,true);
        active = true;
    }
    else{
        anim.setAnimation(&OPEN_PORTAL_G,false,&beam,2,false);
        active = false;
    }
    return true;
}

void Portal::update(){
    GameObject::update();
    vector<const AnimationCode*> completedAnims = anim.updateAnimationFrame();
    for(auto animation : completedAnims){
        if(animation->CODE == MOVE_DISCS.CODE && animation->TYPE == MOVE_DISCS.TYPE && active){
           anim.setAnimation(&OPEN_PORTAL_G,false,&beam);
        }
        if(animation->CODE == OPEN_PORTAL_G.CODE && animation->TYPE == OPEN_PORTAL_G.TYPE && !active){
            anim.setAnimation(&MOVE_DISCS,false,&discs,4,false);
        }
    }
}

bool Portal::highlight(const std::string& srcEntityId){
    if(srcEntityId == "PLAYER"){
        highlighted = true;
    }
    else{
        highlighted = false;
    }
    return highlighted;
}