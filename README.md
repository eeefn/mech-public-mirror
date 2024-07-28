## Mech Game / Game Engine
This is a small game project built in c++ using SDL2. I have been interested in learning how to build core game mechanics from scratch. The majority of the focus so far has been on implementing new mechanics, rather than building a game out of them. So far the engine supports
* Tile based map generation
* Physics and entity collision
* In game map editing 
* Standard animation interface
* Camera system that allows tracking of different entities
* Management of entities, textures, player inputs, and camera

# Dependencies
version: https://github.com/libsdl-org/SDL/releases/tag/release-2.30.0
SDL2-devel-2.30.0-mingw.zip

# Building
Builds are managed with a Makefile in the src directory. The project is designed to build on windows systems. 
    GNU Make 4.4.1
    Built for x86_64-pc-msys
Compiled with g++
    g++.exe (Rev6, Built by MSYS2 project) 13.2.0
