#include "GameObject.h"
#include <unordered_map>

class GameObjectFactory{
    public:
        GameObjectFactory();
        GameObject* makeObject(short objectType, short xT, short yT);
        using ObjectFactory = GameObject*(*)(int id, short xT, short yT);
        std::unordered_map<int,ObjectFactory> objectFactory;
};

extern GameObjectFactory gameObjectFactory;