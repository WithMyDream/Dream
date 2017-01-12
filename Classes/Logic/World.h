#ifndef __World_H__
#define __World_H__

#include "base/CCRef.h"
#include "external/Box2D/Box2D.h"
#include "Unit.h"

class World : public cocos2d::Ref
{
public:
    static World* create();
    
    World();
    ~World();
    bool init();
    
    b2World* getWorld();
    
    void setGravity(float grivaty);
    float getGravity();
    
    void createUnit(ID);
    void destroyUnit();
    
    void pusher(float dt);
private:
    void update(float dt);
    
private:
    b2World*    _b2World;
    float       _gravity;
    
    std::vector<Unit*> _units;
};

#endif // __World_H__
