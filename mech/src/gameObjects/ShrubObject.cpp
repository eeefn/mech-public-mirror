#include "../../headers/gameObjects/ShrubObject.h"
#include "../../headers/TextureManager.h"
#include <iostream>
ShrubObject::ShrubObject(short id, int xT, int yT, short shrubType) : GameObject(2,32,32){
    ID = id;
    xTile = xT;
    yTile = yT;
    objectTexture = textureManager.gameObjectsTexture; 
    spriteSheetPos = {(shrubType) * 32, 32, 32, 32};
}