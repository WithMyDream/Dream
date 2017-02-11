#ifndef __World_H__
#define __World_H__

#include "base/CCRef.h"
#include "Box2D/Box2D.h"
#include "Unit.h"
#include "EventMgr.h"
#include <vector>

extern const float B2SCALE;

class World : public cocos2d::Ref
{
public:
    static World* create();
    
    World();
    ~World();
    bool init();
    
    void setLogicFPS(int logicFPS);
    
    b2World* getB2World(){ return _b2World; }
    
    void setGravity(float grivaty);
    float getGravity(){ return _gravity; }
    
    void loadWorldTMX(const std::string& tmxPath);
    
    Unit* createUnit(int ID);
    void destroyUnit(int index);
    
    void setMainUnit(Unit* unit){ _mainUnit = unit; }
    
    void onJoystick(EventParams &params);
    void onButton(EventParams &params);
    
private:
    void pusher(float dt);
    void update(float dt);
    
private:
    // world time
    int         _logicFPS;
    float       _frameTime;
    float       _pushTime;
    float       _worldTime;
    
    b2World*    _b2World;
    float       _gravity;
    
    std::vector<Unit*> _units;
    Unit*       _mainUnit;      // weak ref
    
    b2ParticleSystem* m_particleSystem;
};

#endif // __World_H__
