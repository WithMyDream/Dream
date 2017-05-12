#ifndef __World_H__
#define __World_H__

#include "base/CCRef.h"
#include "Box2D/Box2D.h"
#include "Unit.h"
#include "Rope.h"
#include "EventMgr.h"
#include <vector>

extern const float B2SCALE;

class QueryCallback : public b2QueryCallback
{
public:
    QueryCallback();
    QueryCallback(std::vector<Unit*>& queryUnits);
    ~QueryCallback();
    bool ReportFixture(b2Fixture* fixture) override;
    bool ShouldQueryParticleSystem(const b2ParticleSystem* particleSystem) override;
private:
    std::vector<Unit*>& _queryUnits;
};

class World : public cocos2d::Ref
{
public:
    static World* create();
    
    World();
    ~World();
    
    // world
    bool init();
    void setLogicFPS(int logicFPS);
    void loadWorldTMX(const std::string& tmxPath);
    
    // physics
    b2World* getB2World(){ return _b2World; }
    void setGravity(float grivaty);
    float getGravity(){ return _gravity; }
    std::vector<Unit*>& queryAABB(Unit* unit);
    std::vector<Unit*>& getQueryUnits(){ return _queryUnits; }
    
    // units
    Unit* createUnit(int ID);
	Rope* createRope(int ID);
    void destroyUnit(int index);
	void destroyUnit(Unit* unit);
    
    // main unit
	void setMainUnit(Unit* unit);
    Unit* getMainUnit() const { return _mainUnit; }
    void setMainUnitViewSize(b2Vec2 size){ _viewSize = size; }
    const b2Vec2& getMainUnitViewSize() const { return _viewSize; }
    
    // input
    void onJoystick(EventParams &params);
    void onButton(EventParams &params);
    
    // test
    Unit* joint1;
    
private:
    void pusher(float dt);
    void update(float dt);
    
private:
    // world
    int         _logicFPS;
    float       _frameTime;
    float       _pushTime;
    float       _worldTime;
    
    // physics
    b2World*    _b2World;
    float       _gravity;
    std::vector<Unit*>  _queryUnits;
    QueryCallback*      _queryCallback;
    
    // units
    std::vector<Unit*> _units;
	std::vector<int> _deleteUnitIndexs;
    
    // main unit
    Unit*       _mainUnit;      // weak ref
    b2Vec2      _viewSize;
    
    b2ParticleSystem* m_particleSystem;
};

#endif // __World_H__
