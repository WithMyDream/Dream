#include "Unit.h"

#include "World.h"

Unit* Unit::create(World* world, int ID)
{
    Unit* unit = new Unit();
    if (unit && unit->init(world, ID))
        unit->autorelease();
    return unit;
}

Unit::Unit()
: _world(nullptr)
, _b2Body(nullptr)
, _ID(-1)
, _jumpImpulseMax(b2Vec2(0.0f, 100.0f))
, _moveVxMax(5.0f)
, _currMoveForce(b2Vec2(0.0f, 0.0f))
, _currDir(-1)
{
    
}

Unit::~Unit()
{
    
}

bool Unit::init(World* world, int ID)
{
    _world = world;
    _ID = ID;
    
    initB2Body();
    
    return true;
}

void Unit::initB2Body()
{
    if (!_world)
        return;
    
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = b2Vec2_zero;
    _b2Body = _world->getB2World()->CreateBody(&bodyDef);
    _b2Body->SetUserData(this);
    
    if (_ID != -1)
    {
        _b2Body->SetTransform(b2Vec2(_world->getMainUnitViewSize().x/2.0f, _world->getMainUnitViewSize().y/2.0f), _b2Body->GetAngle());
        
        b2FixtureDef fixtureDef;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.8f;
        fixtureDef.restitution = 0.0f;
        b2CircleShape circleShape;
        circleShape.m_radius = 50.0f/B2SCALE;
        fixtureDef.shape = &circleShape;
        _b2Body->CreateFixture(&fixtureDef);
    }
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

void Unit::move(float angle)
{
    _moveAngle = angle;
    
    int intAngle = (int)angle;
    CCLOG("[Unit::move] angle : %f -> %d", angle, intAngle);
    if (intAngle == -1)
    {
        _currDir = -1;
        return;
    }
    
    float dirAngle = intAngle + 45.0f;
    int dir = (int)(dirAngle / 90.0f);
    if (_currDir == dir)
        return;
    
    _currDir = dir;
    
    
    // reset
    if (_currDir == 1)       // up
    {
        
    }
    else if (_currDir == 2)  // left
    {
        _b2Body->ApplyLinearImpulse(b2Vec2(-100.0f, 0.0f), _b2Body->GetWorldCenter(), true);
    }
    else if (_currDir == 3)  // down
    {
        
    }
    else                // right
    {
        _b2Body->ApplyLinearImpulse(b2Vec2(100.0f, 0.0f), _b2Body->GetWorldCenter(), true);
    }
    _currDir = -1;
    
}

void Unit::jump()
{
    _b2Body->ApplyLinearImpulse(_jumpImpulseMax, _b2Body->GetWorldCenter(), true);
}

void Unit::hang()
{
    
}


/// -------------------------------------------- update --------------------------------------------

void Unit::_move()
{
    if (_currDir == -1)
        return;
    
    const b2Vec2& currV = _b2Body->GetLinearVelocity();
    float expectedVx = 0;
    
    if (_currDir == 1)       // up
    {
        
    }
    else if (_currDir == 2)  // left
    {
        expectedVx = -_moveVxMax;
    }
    else if (_currDir == 3)  // down
    {
        
    }
    else                // right
    {
        expectedVx = _moveVxMax;
    }
    
    float changeVx = expectedVx - currV.x;
    _currMoveForce.x = _b2Body->GetMass() * changeVx / _delta;
    _b2Body->ApplyForceToCenter(_currMoveForce, true);
}

void Unit::update(float dt)
{
    _delta = dt;
    
    _move();
}
