#include "World.h"

#include <iostream>
#include "base/CCDirector.h"
#include "base/CCScheduler.h"
#include "2d/CCTMXTiledMap.h"

const int LOGICFPS = 60;
const float B2SCALE = 30.0f;

const float InitGravity = -10.0f;
const int VelocityIterations = 10;
const int PositionIterations = 10;

/// -------------------------------------------- QueryCallback --------------------------------------------

QueryCallback::QueryCallback(std::vector<Unit*>& queryUnits)
: _queryUnits(queryUnits)
{
    
}

QueryCallback::~QueryCallback()
{
    
}

bool QueryCallback::ReportFixture(b2Fixture* fixture)
{
    Unit* unit = static_cast<Unit*>(fixture->GetBody()->GetUserData());
	if (unit && unit->getType() == UnitTypeJoint)
	{
		_queryUnits.push_back(unit);
	}
	
	return true;
}

bool QueryCallback::ShouldQueryParticleSystem(const b2ParticleSystem* particleSystem)
{
    return false;
}


/// -------------------------------------------- World --------------------------------------------

World* World::create()
{
    World* world = new World();
    if (world && world->init()) {
        world->autorelease();
    }
    return world;
}

World::World()
: _pushTime(0.0f)
, _worldTime(0.0f)
, _b2World(nullptr)
, _mainUnit(nullptr)
, _queryCallback(nullptr)
{
    _queryUnits.reserve(64);
    _queryCallback = new QueryCallback(_queryUnits);
    _units.reserve(64);
	_deleteUnitIndexs.reserve(64);
    _viewSize.SetZero();
}

World::~World()
{
    delete _queryCallback;
    
    std::vector<Unit*>::iterator it = _units.begin();
    for ( ; it != _units.end(); ++it)
        delete *it;
    delete _b2World;
}

bool World::init()
{
    setLogicFPS(LOGICFPS);
    
    _b2World = new b2World(b2Vec2(0.0f, InitGravity));
    
    cocos2d::Size winSize = cocos2d::Director::getInstance()->getWinSize();
    
    /*
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
     */
    
    
    // test particle system
    b2ParticleSystemDef particleSystemDef;
    m_particleSystem = _b2World->CreateParticleSystem(&particleSystemDef);
    m_particleSystem->SetGravityScale(1.0f);
    m_particleSystem->SetDensity(1.2f);
    m_particleSystem->SetRadius(2.0f/B2SCALE);
    b2ParticleGroupDef pd;
    b2CircleShape shape;
    shape.m_p.Set(winSize.width/B2SCALE, winSize.height/2.0f/B2SCALE);
    shape.m_radius = 50.0f/B2SCALE;
    pd.flags = b2_elasticParticle;
    pd.groupFlags = b2_solidParticleGroup;
    pd.shape = &shape;
    pd.color.Set(255, 0, 0, 255);
    m_particleSystem->CreateParticleGroup(pd);
    
    cocos2d::Scheduler* scheduler = cocos2d::Director::getInstance()->getScheduler();
    scheduler->schedule(CC_SCHEDULE_SELECTOR(World::pusher), this, 0, false);
    
    REGISTER_EVENT(EventJoystick, onJoystick);
    REGISTER_EVENT(EventButton, onButton);
    
    
    
    return true;
}

void World::setLogicFPS(int logicFPS)
{
    _logicFPS = logicFPS;
    _frameTime = 1.0f/_logicFPS;
}

// TODO :
// value map is assigned as a copy,
// it should be optimized as a reference.
void World::loadWorldTMX(const std::string& tmxPath)
{
    cocos2d::TMXTiledMap* tmxMap = cocos2d::TMXTiledMap::create(tmxPath);
    cocos2d::TMXObjectGroup* logicLayer = tmxMap->getObjectGroup("logic");
    float mapHeight = tmxMap->getMapSize().height * tmxMap->getTileSize().height;
    
    const cocos2d::ValueVector& valueVector = logicLayer->getObjects();
    cocos2d::ValueVector::const_iterator it = valueVector.begin();
    int i = 0;
    for ( ; it!=valueVector.end(); ++it)
    {
        std::cout<<"object group "<<++i;
        std::cout<<it->getDescription();
        cocos2d::ValueMap dict = it->asValueMap();
        std::string name = dict["name"].asString();
        std::string type = dict["type"].asString();
        float x = dict["x"].asFloat();
        float y = dict["y"].asFloat();
        float width = dict["width"].asFloat();
        float height = dict["height"].asFloat();
        
        if ("box" == type)
        {
            /**/
            Unit* unit = createUnit(-1);
			unit->setName(name);
            b2Body* b2body = unit->getB2Body();
            b2body->SetType(b2_staticBody);
            
            b2Vec2 pos(x/B2SCALE + width/2.0f/B2SCALE, y/B2SCALE + height/2.0f/B2SCALE);
            unit->setPosition(pos);
            
            b2FixtureDef fixtureDef;
            fixtureDef.density = 1.0f;
            fixtureDef.friction = 0.8f;
            fixtureDef.restitution = 0.4f;
            b2PolygonShape polygon;
            polygon.SetAsBox(width/2.0f/B2SCALE, height/2.0f/B2SCALE);
            fixtureDef.shape = &polygon;
            b2body->CreateFixture(&fixtureDef);
            
            if ("joint1" == name)
            {
                joint1 = unit;
				unit->setType(UnitTypeJoint);
            }
            else if ("joint" == name)
            {
                unit->setType(UnitTypeJoint);
            }
			else if ("ground" == name)
			{
				unit->setType(UnitTypeGround);
			}
            
        }
        else if ("edge" == type)
        {
            Unit* unit = createUnit(-1);
			unit->setName(name);
            b2Body* b2body = unit->getB2Body();
            b2body->SetType(b2_staticBody);
            
            b2FixtureDef fixtureDef;
            fixtureDef.density = 1.0f;
            fixtureDef.friction = 0.8f;
            fixtureDef.restitution = 0.4f;
            b2EdgeShape edgeShap;
            fixtureDef.shape = &edgeShap;
            
            cocos2d::ValueVector points = dict["polylinePoints"].asValueVector();
            float prevX = 0.0f;
            float prevY = 0.0f;
            for (int i = 0; i < points.size(); ++i)
            {
                cocos2d::ValueMap posMap = points[i].asValueMap();
                float pointX = posMap["x"].asFloat();
                float pointY = posMap["y"].asFloat();
                if (i > 0) {
                    float x1 = x + prevX;
                    float y1 = y - prevY;
                    float x2 = x + pointX;
                    float y2 = y - pointY;
                    //CCLOG("%f, %f, %f, %f", x1, y1, x2, y2);
                    edgeShap.Set(b2Vec2(x1/B2SCALE, y1/B2SCALE), b2Vec2(x2/B2SCALE, y2/B2SCALE));
                    b2body->CreateFixture(&fixtureDef);
                }
                prevX = pointX;
                prevY = pointY;
            }

			if ("barrier" == name)
			{
				joint1 = unit;
				unit->setType(UnitTypeBarrier);
			}
			else if ("frame" == name)
			{
				unit->setType(UnitTypeFrame);
			}
        }
    }
}

void World::setGravity(float grivaty)
{
    _gravity = grivaty;
    _b2World->SetGravity(b2Vec2(0.0f, _gravity));
}

std::vector<Unit*>& World::queryAABB(Unit* unit)
{
    _queryUnits.clear();
    const b2Vec2& mainPos = unit->getPostion();
    b2AABB aabb;
    aabb.lowerBound = b2Vec2(mainPos.x - _viewSize.x/2.0f, mainPos.y - _viewSize.y/2.0f);
    aabb.upperBound = b2Vec2(mainPos.x + _viewSize.x/2.0f, mainPos.y + _viewSize.y/2.0f);
    _b2World->QueryAABB(_queryCallback, aabb);
    
	return _queryUnits;
}

Unit* World::createUnit(int ID)
{
    Unit* unit = Unit::create(this, ID);
    
    unit->retain();
    _units.push_back(unit);
    
	ECreateUnit params(unit);
	EventMgr::getInatence()->notify(params);
    
    return unit;
}

Rope* World::createRope(int ID)
{
    Rope* rope = Rope::create(this, ID);
    
    rope->retain();
    _units.push_back(rope);
    
	ECreateUnit params(rope);
	EventMgr::getInatence()->notify(params);
    
    return rope;
}

void World::destroyUnit(int index)
{
	if (index < 0 || index > _units.size() - 1)
		return;

	_units[index]->destroy();
}

void World::destroyUnit(Unit* unit)
{
	unit->destroy();

	EDestroyUnit params(unit);
	EventMgr::getInatence()->notify(params);
}

void World::setMainUnit(Unit* unit)
{
	_mainUnit = unit;

	ESetMainUnit params(_mainUnit);
	EventMgr::getInatence()->notify(params);
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
    EButton& button = static_cast<EButton&>(params);
    //CCLOG("[World::onButton] index : %d", button._index);
    
    if (_mainUnit)
        _mainUnit->hang(nullptr);
}

void World::pusher(float dt)
{
    _pushTime += dt;
    //CCLOG("[World::update] %f", dt);
    
    int updateCount = (int)((_pushTime - _worldTime) / _frameTime);
    for (int i = 0; i < updateCount; ++i)
        update(_frameTime);
    _worldTime += updateCount * _frameTime;
}

void World::update(float dt)
{
    
    // update box2d world
    _b2World->Step(dt, VelocityIterations, PositionIterations);
    
    // update units
	_deleteUnitIndexs.clear();
	int num = _units.size();
	for (int i = 0; i < num; ++i)
	{
		Unit* unit = _units[i];
		unit->update(dt);
		if (unit->isDestroy())
		{
			_deleteUnitIndexs.push_back(i);
		}
	}

	// handle delete
	int deleteNum = _deleteUnitIndexs.size();
	for (int i = 0; i < deleteNum; ++i)
	{
		int deleteIndex = _deleteUnitIndexs[i];
		int backIndex = num - 1 - i;
		Unit* tempUnit = _units[backIndex];
		_units[backIndex] = _units[deleteIndex];
		_units[deleteIndex] = tempUnit;
	}
	for (int i = 0; i < deleteNum; ++i)
	{
        Unit* deleteUnit = _units.back();
        deleteUnit->end();
		deleteUnit->release();
		_units.pop_back();
	}
}
