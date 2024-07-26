#pragma once
#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)
extern struct MapInfo{
    constexpr static int MAX_LVL_HEIGHT = 200;
    constexpr static int MAX_LVL_WIDTH = 200; 
    constexpr static int TEX_DIM = 8; 
    constexpr static int TILE_DIM = 16; 
    constexpr static int TILES_IN_MAP = (64 / TILE_DIM);
    constexpr static int TILE_WIDTH_IN_TILE_MAP = (64 / TEX_DIM);
} mapInfo;

extern struct Gamemodes{
    constexpr static int EDIT = 1;
    constexpr static int PLAY = 0;
} gamemodes;
