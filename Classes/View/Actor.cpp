#include "Actor.h"

Actor* Actor::create()
{
    Actor* actor = new Actor();
    if (actor && actor->init()) {
        actor->autorelease();
    }
    return actor;
}

Actor::Actor()
{
    
}

Actor::~Actor()
{
    
}

bool Actor::init()
{
    
    
    return true;
}

void Actor::update(float dt)
{
    
}
