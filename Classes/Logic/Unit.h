#ifndef __Unit_H__
#define __Unit_H__

#include "base/CCRef.h"
#include "external/Box2D/Box2D.h"

class Unit : public cocos2d::Ref
{
public:
    static Unit* create();
    
    Unit();
    ~Unit();
    bool init();
    
    void update(float dt);
    
private:
    
    
private:
    b2Body*     _b2Body;
};

#endif // __Unit_H__
