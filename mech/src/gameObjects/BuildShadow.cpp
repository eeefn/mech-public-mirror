#include "../../headers/gameObjects/BuildShadow.h"
#include "../../headers/gameObjects/GameObjectManager.h"
#include "../../headers/WindowManager.h"
#include "../../headers/PlayerState.h"
#include "../../headers/TextureManager.h"
#include "../../headers/Camera.h"

BuildShadow::BuildShadow(){
   return; 
}

BuildShadow::~BuildShadow(){
    if(shadowObject != nullptr){
        delete shadowObject;
    }
    shadowObject = nullptr;
}


void BuildShadow::render(){
    if(!playerState.inventoryOpen && (shadowObject != nullptr)){
        if(checkValidPlacement()){
            //render shadow tinted green
            SDL_SetTextureColorMod(textureManager.gameObjectsTexture,0,0xFF,0);
            SDL_SetTextureAlphaMod(textureManager.gameObjectsTexture,128);
            shadowObject->render(windowManager.renderer);
            SDL_SetTextureColorMod(textureManager.gameObjectsTexture,0xFF,0xFF,0xFF);
            SDL_SetTextureAlphaMod(textureManager.gameObjectsTexture,0xFF);
        }
        else{
            SDL_SetTextureColorMod(textureManager.gameObjectsTexture,0xFF,0,0);
            SDL_SetTextureAlphaMod(textureManager.gameObjectsTexture,128);
            shadowObject->render(windowManager.renderer);
            SDL_SetTextureColorMod(textureManager.gameObjectsTexture,0xFF,0xFF,0xFF);
            SDL_SetTextureAlphaMod(textureManager.gameObjectsTexture,0xFF);
            //render shadow tinted red
        }    
    }
}


void BuildShadow::update(){
    if(shadowObject != nullptr){
        SDL_Point shadowPosOnScreen = {0,0}; //poll cursor pos ;
        SDL_GetMouseState(&shadowPosOnScreen.x,&shadowPosOnScreen.y);
        snapCenterPoint(&shadowPosOnScreen);
        shadowObject->renderRects.posOnScreen.x = shadowPosOnScreen.x;
        shadowObject->renderRects.posOnScreen.y = shadowPosOnScreen.y;
        shadowObject->xTile = camera.getGlobalXPosFromFrame(shadowPosOnScreen.x) / mapInfo.TILE_DIM;
        shadowObject->yTile = camera.getGlobalXPosFromFrame(shadowPosOnScreen.y) / mapInfo.TILE_DIM;
    }
}

/*-Modifies the given point to refer to the top left corner of the shadowObject
-Modifies the point to snap to the tileMap grid boundaries*/
void BuildShadow::snapCenterPoint(SDL_Point* pointToSnapAndCenter){
    //center
    pointToSnapAndCenter->x -= shadowObject->scaledWidth / 2;
    pointToSnapAndCenter->y -= shadowObject->scaledHeight / 2;
    //snap
    camera.snapPointToTileMap(pointToSnapAndCenter);
}

void BuildShadow::setShadowObject(short objectType){
    if(shadowObject == nullptr){
        shadowObject = gameObjectManager.makeUnmanagedObject(objectType,-1,-1);
    }
    else{
        if(shadowObject->ID != objectType) {
            delete shadowObject;
            shadowObject = gameObjectManager.makeUnmanagedObject(objectType,-1,-1);
        }
    }
}

void BuildShadow::destroyShadowObject(){
    delete shadowObject;
    shadowObject = nullptr;
}

bool BuildShadow::checkValidPlacement(){
    if(!gameObjectManager.checkObjectObjectListCollision(shadowObject)){
        if(true/*!collider.checkGameObjectTilemapCollision()*/){
            return true;
        }
    }
    return false;
}

bool BuildShadow::placeShadowObject(){
    return false; 
}