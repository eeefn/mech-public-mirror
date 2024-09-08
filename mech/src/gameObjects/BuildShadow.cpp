#include "../../headers/gameObjects/BuildShadow.h"
#include "../../headers/gameObjects/GameObjectManager.h"

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
    if(false/*inventory != open && buildShadow != nullptr*/){
        if(checkValidPlacement()){
            //render shadow tinted green
        }
        else{
            //render shadow tinted red
        }    
    }
}


void BuildShadow::update(){
    if(shadowObject != nullptr){
        SDL_Point shadowPosOnScreen = {0,0}; //poll cursor pos ;
        snapCenterPoint(&shadowPosOnScreen);
        shadowObject->renderRects.posOnScreen.x = shadowPosOnScreen.x;
        shadowObject->renderRects.posOnScreen.y = shadowPosOnScreen.y;
    }
}

/*-Modifies the given point to refer to the top left corner of the shadowObject
-Modifies the point to snap to the tileMap grid boundaries*/
void BuildShadow::snapCenterPoint(SDL_Point* pointToSnapAndCenter){
    //center
    pointToSnapAndCenter->x += shadowObject->scaledWidth / 2;
    pointToSnapAndCenter->y += shadowObject->scaledHeight / 2;
    //snap
    //camera.snapPointToTileMap(pointToSnapAndCenter);
}

void BuildShadow::setShadowObject(short objectType){
    if(shadowObject == nullptr){
        shadowObject = nullptr /*gameObjectManager.makeUnmanagedObject(objectType,-1,-1)*/;
    }
    else{
        if(shadowObject->ID != objectType) {
            delete shadowObject;
            shadowObject = nullptr/*gameObjectManager.makeUnmanagedObject(objectType,-1,-1)*/;
        }
    }
}

void BuildShadow::destroyShadowObject(){
    delete shadowObject;
    shadowObject = nullptr;
}

bool BuildShadow::checkValidPlacement(){
    return false;
}

bool BuildShadow::placeShadowObject(){
    return false; 
}