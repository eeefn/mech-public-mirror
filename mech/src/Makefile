TARGET=main.exe
FLAGS=--std=c++14
INCLUDEPATH=$(USERPROFILE)/SDL2/x86_64-w64-mingw32/include/SDL2/
LIBRARYPATH=$(USERPROFILE)/SDL2/x86_64-w64-mingw32/lib
BUILD_DIR=build
cc=g++

CPP = $(wildcard *.cpp) $(wildcard entities/*.cpp) $(wildcard controller/*.cpp) $(wildcard gameObjects/*.cpp) $(wildcard items/*.cpp)
OBJ = $(CPP:%.cpp=$(BUILD_DIR)/%.o)
DEP = $(OBJ:%.o=%.d)

#default target
$(TARGET): $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET) : $(OBJ) 
	$(cc) --std=c++14 $^ -o $@ -L $(LIBRARYPATH) -lmingw32 -lSDL2main -lSDL2 

-include $(DEP)

$(BUILD_DIR)/%.o : %.cpp
	$(cc) $(FLAGS) -MMD -c $< -o $@ -I $(INCLUDEPATH) -L $(LIBRARYPATH) -lmingw32 -lSDL2main -lSDL2

.PHONY : clean
clean :
	rm $(OBJ) $(DEP)