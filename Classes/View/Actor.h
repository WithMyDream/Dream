#ifndef __Actor_H__
#define __Actor_H__

#include "cocos2d.h"
using namespace cocos2d;

class Actor : public Node
{
public:
    static Actor* create();
    
    Actor();
    ~Actor();
    bool init();
    
    void update(float dt);
    
private:
    
    
private:
    
};

#endif // __Actor_H__
