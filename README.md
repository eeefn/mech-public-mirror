## Mech Game / Game Engine
This is a small game project built in c++ using SDL2. I have been interested in learning how to build core game mechanics from scratch, and this project has been an exercise in emulating common mechanics in 2D games. Currently, the engine supports
* Tile based map generation, in game map editing
* Camera that can follow any entity
* Inventories, crafting

  <img src = "https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExOWxzZjJyODY1MTF1bzlvbXp1MmNtOG10bzRqMnBqZXEzMXZpeGZ1OSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/bpqSzYb8ewvuz81Fsw/giphy.gif" width = 400>
  
* Resource collection
  
  <img src = "https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExcnN2YzYzejY1YThkeW5nZzkyOGNtNWdlaW50anluNTVyY3YzeWN1OCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/6FGV9nWrYixlkq383h/giphy.gif" width=200>
 
* Placing objects in the world from inventory

  <img src = "https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExZHl3cmN2aXgybWF6ajVudGQ5ZG01eGc0MG9zdnVoOGg3aXIxMHdwbSZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/qEktt1RcI7TUQq9ikJ/giphy.gif" width = 200>
* Physics reactive, layered animations for objects, entities, and items.

  <img src = "https://i.giphy.com/media/v1.Y2lkPTc5MGI3NjExdGZhcXl6ZTZidjNwYTl6czN1NjFzdXZiZjFwejZjY2MwOXNncDZqYyZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/jlsFuS6McGP0LGqrZR/giphy.gif" width = 200>

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
