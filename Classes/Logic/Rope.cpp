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
: _firstUnit(nullptr)
, _lastUnit(nullptr)
, _ropeRadius(2.0f/B2SCALE)
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
    
	/*
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
    
    for (int i=0; i<5; ++i)
        addOneBody();
	*/
}

void Rope::clear()
{
	for (int i = 0; i < _b2Bodies.size(); ++i)
	{
		b2Body* body = _b2Bodies[i];
		_world->getB2World()->DestroyBody(body);
	}
	_b2Bodies.clear();

	for (int i = 0; i < _b2Joints.size(); ++i)
	{
		b2Joint* joint = _b2Joints[i];
		_world->getB2World()->DestroyJoint(joint);
	}
	_b2Joints.clear();

	_firstUnit = nullptr;
	_lastUnit = nullptr;
}

void Rope::addOneBody(float angle, bool isLast)
{
	// last body
	b2Body* prevBody = nullptr;
	b2Body* currBody = nullptr;
	if (_b2Bodies.empty())
	{
		prevBody = _firstUnit->getB2Body();
	}
	else
	{
		prevBody = getLastBody();
	}
	float prevX = prevBody->GetPosition().x;
	float prevY = prevBody->GetPosition().y;
	float currX = prevX + cos(angle) * RopeBodyOffset;
	float currY = prevY + sin(angle) * RopeBodyOffset;

	// body
	if (!isLast)
	{
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position = b2Vec2(currX, currY);
		bodyDef.angle = angle;
		currBody = _world->getB2World()->CreateBody(&bodyDef);
		b2FixtureDef fixtureDef;
		b2PolygonShape polygonShape;
		polygonShape.SetAsBox(_ropeRadius, RopeBodyOffset / 2.0f);
		fixtureDef.shape = &polygonShape;
		fixtureDef.density = 100;
		fixtureDef.friction = 0.5;
		fixtureDef.restitution = 0.2;
		currBody->CreateFixture(&fixtureDef);
		_b2Bodies.push_back(currBody);
	}
	else
	{
		currBody = _lastUnit->getB2Body();
	}

	// joint
	b2RevoluteJointDef distanceJointDef;
	distanceJointDef.Initialize(prevBody, currBody, b2Vec2((prevX + currX)/2.0f, (prevY + currY) / 2.0f));
	b2Joint* joint = _world->getB2World()->CreateJoint(&distanceJointDef);
	_b2Joints.push_back(joint);
}

void Rope::linkUnits(Unit* first, Unit* last)
{
	if (!first || !last)
		return;

	clear();

	_firstUnit = first;
	_lastUnit = last;

	b2Body* body1 = _firstUnit->getB2Body();
	float x1 = body1->GetPosition().x;
	float y1 = body1->GetPosition().y;

	b2Body* body2 = _lastUnit->getB2Body();
	float x2 = body2->GetPosition().x;
	float y2 = body2->GetPosition().y;

	// last -> first
	float disX = x1 - x2;
	float disY = y1 - y2;
	
	float dis = sqrt(disX * disX + disY * disY);
	float angle = disX == 0.0f ? (disY > 0.0f ? 0.5f*b2_pi : 1.5f*b2_pi) : atan(disY/disX);
	int count = (int)dis / RopeBodyOffset;


	for (int i = 0; i < count; ++i)
	{
		addOneBody(angle, i == count - 1);
	}
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
