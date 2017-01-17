#ifndef __Actor_H__
#define __Actor_H__

#include "cocos2d.h"
#include "../Logic/Unit.h"
#include "../Logic/World.h"

using namespace cocos2d;

class Actor : public Node
{
public:
    static Actor* create();
    
    Actor();
    ~Actor();
    bool init();
    
    void setUnit(Unit* unit){_unit = unit; }
    
    void update(float dt);
    
private:
    
    
private:
    Unit* _unit;    // weak ref
};

#endif // __Actor_H__
