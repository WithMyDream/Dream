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
:_unit(nullptr)
{
    
}

Actor::~Actor()
{
    _unit = nullptr;
}

bool Actor::init()
{
    Sprite* sprite = Sprite::create("HelloWorld.png");
    addChild(sprite);
    
    return true;
}

void Actor::update(float dt)
{   
    if (!_unit)
        return;
    
    const b2Vec2& pos = _unit->getPostion();
    setPosition(pos.x*B2SCALE, pos.y*B2SCALE);
    setRotation(CC_RADIANS_TO_DEGREES(_unit->getAngle()));
}
