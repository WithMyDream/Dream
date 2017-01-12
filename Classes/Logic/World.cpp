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
:_b2World(nullptr)
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
    b2BodyDef worldFrameBodyDef;
    b2Body* worldFrameBody = _b2World->CreateBody(&worldFrameBodyDef);
    b2FixtureDef worldFrameFixtureDef;
    b2EdgeShape worldFrameEdge;
    worldFrameFixtureDef.shape = &worldFrameEdge;
    // bottom
    worldFrameEdge.Set(b2Vec2(0.0f, 0.0f), b2Vec2(winSize.width/B2SCALE, 0.0f));
    worldFrameBody->CreateFixture(&worldFrameFixtureDef);
    // left
    worldFrameEdge.Set(b2Vec2(0.0f, 0.0f), b2Vec2(0.0f, winSize.height/B2SCALE));
    worldFrameBody->CreateFixture(&worldFrameFixtureDef);
    // right
    worldFrameEdge.Set(b2Vec2(winSize.width/B2SCALE, 0.0f), b2Vec2(winSize.width/B2SCALE, winSize.height/B2SCALE));
    worldFrameBody->CreateFixture(&worldFrameFixtureDef);
    // top
    worldFrameEdge.Set(b2Vec2(0.0f, winSize.height/B2SCALE), b2Vec2(winSize.width/B2SCALE, winSize.height/B2SCALE));
    worldFrameBody->CreateFixture(&worldFrameFixtureDef);
    
    cocos2d::Scheduler* scheduler = cocos2d::Director::getInstance()->getScheduler();
    scheduler->schedule(CC_SCHEDULE_SELECTOR(World::pusher), this, 0, false);
    
    return true;
}

void World::setGravity(float grivaty)
{
    _gravity = grivaty;
    _b2World->SetGravity(b2Vec2(0.0f, _gravity));
}

float World::getGravity()
{
    return _gravity;
}

void World::pusher(float dt)
{
    update(dt);
}

void World::update(float dt)
{
    _b2World->Step(dt, VelocityIterations, PositionIterations);
}
