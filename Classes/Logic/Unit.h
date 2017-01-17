#ifndef __Unit_H__
#define __Unit_H__

#include "base/CCRef.h"
#include "external/Box2D/Box2D.h"

class World;

class Unit : public cocos2d::Ref
{
public:
    static Unit* create(World* world);
    
    Unit();
    ~Unit();
    bool init(World* world);
    
    b2Body* getB2Body(){ return _b2Body; }
    
    void setPosition(b2Vec2 &pos);
    const b2Vec2& getPostion();
    
    void setAngle(float32 angle);
    float32 getAngle();
    
    void update(float dt);
    
private:
    
    
private:
    b2Body*     _b2Body;
};

#endif // __Unit_H__
