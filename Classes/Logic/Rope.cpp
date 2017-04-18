#include "Rope.h"

#include "World.h"
#include "base/CCDirector.h"

const float RopeBodyOffset = 10.0f/B2SCALE;

Rope* Rope::create(World* world, int ID)
{
    Rope* rope = new Rope();
    if (rope && rope->init(world, ID))
        rope->autorelease();
    return rope;
}

Rope::Rope()
: _ropeRadius(2.0f/B2SCALE)
{
    _b2Bodies.reserve(8);
    _b2Joints.reserve(8);
}

Rope::~Rope()
{
    
}

bool Rope::init(World* world, int ID)
{
    Unit::init(world, ID);
    
    return true;
}

void Rope::initB2Body()
{
    if (!_world)
        return;
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2_zero;
    _b2Body = _world->getB2World()->CreateBody(&bodyDef);
    _b2Body->SetUserData(this);
    
    cocos2d::Size winSize = cocos2d::Director::getInstance()->getWinSize();
    _b2Body->SetTransform(b2Vec2(winSize.width/2.0f/B2SCALE, winSize.height/2.0f/B2SCALE), _b2Body->GetAngle());
    
    b2FixtureDef fixtureDef;
    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(_ropeRadius, RopeBodyOffset/2.0f);
    fixtureDef.shape = &polygonShape;
    fixtureDef.density = 100;
    fixtureDef.friction = 0.5;
    fixtureDef.restitution = 0.2;
    _b2Body->CreateFixture(&fixtureDef);
    
    _b2Bodies.push_back(_b2Body);
    
    for (int i=0; i<20; ++i)
        addOneBody();
}

void Rope::addOneBody()
{
    // last body
    size_t i = _b2Bodies.size();
    b2Body* lastBody = getLastBody();
    float x = lastBody->GetPosition().x;
    float y = lastBody->GetPosition().y;
    
    // body
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2(x, y - RopeBodyOffset);
    b2Body* body = _world->getB2World()->CreateBody(&bodyDef);
    b2FixtureDef fixtureDef;
    b2PolygonShape polygonShape;
    polygonShape.SetAsBox(_ropeRadius, RopeBodyOffset/2.0f);
    fixtureDef.shape = &polygonShape;
    fixtureDef.density=100;
    fixtureDef.friction=0.5;
    fixtureDef.restitution=0.2;
    body->CreateFixture(&fixtureDef);
    _b2Bodies.push_back(body);
    
    // joint
    b2RevoluteJointDef distanceJointDef;
    distanceJointDef.Initialize(_b2Bodies[i - 1], _b2Bodies[i], b2Vec2(x, y - RopeBodyOffset/2.0f));
    b2Joint* joint = _world->getB2World()->CreateJoint(&distanceJointDef);
    _b2Joints.push_back(joint);
}

void Rope::jointFirstTo(Unit* unit)
{
    b2Body* body = unit->getB2Body();
    float x = body->GetPosition().x;
    float y = body->GetPosition().y;
    
    b2RevoluteJointDef distanceJointDef;
    distanceJointDef.Initialize(body, getFirstBody(), b2Vec2(x, y - RopeBodyOffset/2.0f));
    _world->getB2World()->CreateJoint(&distanceJointDef);
    
    b2Vec2 pos = body->GetPosition();
    setPosition(pos);
}

void Rope::jointLastTo(Unit* unit)
{
    b2Body* body = unit->getB2Body();
    float x = getLastBody()->GetPosition().x;
    float y = getLastBody()->GetPosition().y;
    
    b2Vec2 pos(x, y);
    unit->setPosition(pos);
    
    b2RevoluteJointDef distanceJointDef;
    distanceJointDef.Initialize(getLastBody(), body, b2Vec2(x, y - RopeBodyOffset/2.0f));
    _world->getB2World()->CreateJoint(&distanceJointDef);
}

void Rope::setPosition(b2Vec2 &pos)
{
    for (int i=0; i<_b2Bodies.size(); ++i)
    {
        b2Body* body = _b2Bodies[i];
        body->SetTransform(b2Vec2(pos.x, pos.y - RopeBodyOffset*(i+1)), 0.0f);
        //@TODO set joints's pos
        /*
        if (i > 0)
        {
            b2Joint* joint = _b2Joints[i];
            joint->SetTransform(pos, joint->GetAngle());
        }
         */
    }
}

const b2Vec2& Rope::getPostion()
{
    b2Body* body = getFirstBody();
    return body->GetPosition();
}

void Rope::setAngle(float32 angle)
{
    b2Body* body = getFirstBody();
    body->SetTransform(body->GetPosition(), angle);
}

float32 Rope::getAngle()
{
    b2Body* body = getFirstBody();
    return body->GetAngle();
}

void Rope::setRopeRadius(float ropeRadius)
{
    if (_ropeRadius == ropeRadius)
        return;
    
    _ropeRadius = ropeRadius;
    
    //@TODO set bodies's box witdh
}

void Rope::update(float dt)
{
    Unit::update(dt);
    
    
}
