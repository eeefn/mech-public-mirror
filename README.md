## Mech Game / Game Engine
This is a small game project built in c++ using SDL2. I have been interested in learning how to build core game mechanics from scratch. The majority of the focus so far has been on implementing new mechanics, rather than building a game out of them. So far the engine supports
* Tile based map generation
* In game map editing
* Camera system that allows tracking of different entities
* Inventories, crafting, resource collection

  <img src = "https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExcnN2YzYzejY1YThkeW5nZzkyOGNtNWdlaW50anluNTVyY3YzeWN1OCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/6FGV9nWrYixlkq383h/giphy.gif" width=200>
  
* Entities, GameObjects, Items
* Standard animation interface that allows for distinct layered animations.
* 

# Dependencies
version: https://github.com/libsdl-org/SDL/releases/tag/release-2.30.0
SDL2-devel-2.30.0-mingw.zip

# Building
Builds are managed with a Makefile in the src directory. The project is designed to build on windows systems. 
    GNU Make 4.4.1
    Built for x86_64-pc-msys
Compiled with g++
    g++.exe (Rev6, Built by MSYS2 project) 13.2.0
# Playing
