#include "World.h"

#include "base/CCDirector.h"
#include "base/CCScheduler.h"

const float InitGravity = -10.0f;
const int VelocityIterations = 10;
const int PositionIterations = 10;
const float B2SCALE = 30.0f;

World* World::create()
{
    World* world = new World();
    if (world && world->init()) {
        world->autorelease();
    }
    return world;
}

World::World()
: _b2World(nullptr)
, _mainUnit(nullptr)
{
    
}

World::~World()
{
    std::vector<Unit*>::iterator it = _units.begin();
    for ( ; it != _units.end(); ++it)
        delete *it;
    delete _b2World;
}

bool World::init()
{
    _b2World = new b2World(b2Vec2(0.0f, InitGravity));
    
    cocos2d::Size winSize = cocos2d::Director::getInstance()->getWinSize();
    
    // base world frame
    b2BodyDef bodyDef;
    b2Body* body = _b2World->CreateBody(&bodyDef);
    body->SetUserData(this);
    b2FixtureDef fixtureDef;
    b2EdgeShape edgeShap;
    fixtureDef.shape = &edgeShap;
    // bottom
    edgeShap.Set(b2Vec2(0.0f, 0.0f), b2Vec2(winSize.width/B2SCALE, 0.0f));
    body->CreateFixture(&fixtureDef);
    // left
    edgeShap.Set(b2Vec2(0.0f, 0.0f), b2Vec2(0.0f, winSize.height/B2SCALE));
    body->CreateFixture(&fixtureDef);
    // right
    edgeShap.Set(b2Vec2(winSize.width/B2SCALE, 0.0f), b2Vec2(winSize.width/B2SCALE, winSize.height/B2SCALE));
    body->CreateFixture(&fixtureDef);
    // top
    edgeShap.Set(b2Vec2(0.0f, winSize.height/B2SCALE), b2Vec2(winSize.width/B2SCALE, winSize.height/B2SCALE));
    body->CreateFixture(&fixtureDef);
    
    cocos2d::Scheduler* scheduler = cocos2d::Director::getInstance()->getScheduler();
    scheduler->schedule(CC_SCHEDULE_SELECTOR(World::pusher), this, 0, false);
    
    REGISTER_EVENT(EventJoystick, onJoystick);
    REGISTER_EVENT(EventButton, onButton);
    
    return true;
}

void World::setGravity(float grivaty)
{
    _gravity = grivaty;
    _b2World->SetGravity(b2Vec2(0.0f, _gravity));
}

void World::createUnit(int ID)
{
    Unit* unit = Unit::create(this);
    unit->retain();
    _units.push_back(unit);
    
    _mainUnit = unit;
    
    ECreateUnit params(unit);
    EventMgr::getInatence()->notify(params);
}

void World::destroyUnit(int index)
{
    
}

void World::onJoystick(EventParams &params)
{
    EJoystick joystick = static_cast<EJoystick&>(params);
    //CCLOG("[World::onJoystick] angle : %f", joystick._angle);
    
    if (_mainUnit)
        _mainUnit->move(joystick._angle);
}

void World::onButton(EventParams &params)
{
    EButton button = static_cast<EButton&>(params);
    //CCLOG("[World::onButton] index : %d", button._index);
    
    if (_mainUnit)
        _mainUnit->jump();
}

void World::pusher(float dt)
{
    update(dt);
}

void World::update(float dt)
{
    //CCLOG("[World::update] %f", dt);
    _b2World->Step(dt, VelocityIterations, PositionIterations);
    
    std::vector<Unit*>::iterator it = _units.begin();
    for ( ; it != _units.end(); ++it)
        (*it)->update(dt);
}
