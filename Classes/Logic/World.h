#ifndef __World_H__
#define __World_H__

#include "base/CCRef.h"
#include "Box2D/Box2D.h"
#include "Unit.h"
#include <vector>

extern const float B2SCALE;

class World : public cocos2d::Ref
{
public:
    static World* create();
    
    World();
    ~World();
    bool init();
    
    b2World* getB2World(){ return _b2World; }
    
    void setGravity(float grivaty);
    float getGravity(){ return _gravity; }
    
    void createUnit(int ID);
    void destroyUnit(int index);
    
    void pusher(float dt);
private:
    void update(float dt);
    
private:
    b2World*    _b2World;
    float       _gravity;
    
    std::vector<Unit*> _units;
};

#endif // __World_H__
