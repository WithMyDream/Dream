#include "Unit.h"

#include "World.h"
#include "base/CCDirector.h"

Unit* Unit::create(World* world)
{
    Unit* unit = new Unit();
    if (unit && unit->init(world)) {
        unit->autorelease();
    }
    return unit;
}

Unit::Unit()
:_b2Body(nullptr)
{
    
}

Unit::~Unit()
{
    
}

bool Unit::init(World* world)
{
    cocos2d::Size winSize = cocos2d::Director::getInstance()->getWinSize();
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2(winSize.width/2.0f/B2SCALE, winSize.height/2.0f/B2SCALE);
    _b2Body = world->getB2World()->CreateBody(&bodyDef);
    _b2Body->SetUserData(this);
    b2FixtureDef fixtureDef;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.2f;
    fixtureDef.restitution = 0.8f;
    b2CircleShape circleShap;
    fixtureDef.shape = &circleShap;
    circleShap.m_radius = 50.0f/B2SCALE;
    _b2Body->CreateFixture(&fixtureDef);
    
    return true;
}

void Unit::setPosition(b2Vec2 &pos)
{
    _b2Body->SetTransform(pos, _b2Body->GetAngle());
}

const b2Vec2& Unit::getPostion()
{
    return _b2Body->GetPosition();
}

void Unit::setAngle(float32 angle)
{
    _b2Body->SetTransform(_b2Body->GetPosition(), angle);
}

float32 Unit::getAngle()
{
    return _b2Body->GetAngle();
}

void Unit::update(float dt)
{
    
}
