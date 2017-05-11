#ifndef __Rope_H__
#define __Rope_H__

#include "Unit.h"
#include <vector>

class Rope : public Unit
{
public:
    static Rope* create(World* world, int ID);
    
    Rope();
    ~Rope();
    bool init(World* world, int ID) override;
    void end() override;
    
    void initB2Body() override;
    b2Body* getB2Body() override { return getFirstBody(); }
    
    std::vector<b2Body*>& getB2Bodies(){ return _b2Bodies; }
    b2Body* getFirstBody(){ return _b2Bodies.front(); }
    b2Body* getLastBody(){ return _b2Bodies.back(); }
	void linkUnits(Unit* first, Unit* last);
    void jointFirstTo(Unit* unit);
    void jointLastTo(Unit* unit);

    void setPosition(b2Vec2 &pos) override;
    const b2Vec2& getPostion() override;
    
    void setAngle(float32 angle) override;
    float32 getAngle() override;
    
    void setRopeRadius(float ropeRadius);
    
    void update(float dt) override;
    
private:
	void clear();
	void addOneBody(float angle, bool isLast);

private:
    std::vector<b2Body*>    _b2Bodies;
    std::vector<b2Joint*>   _b2Joints;

	Unit*					_firstUnit;
	Unit*					_lastUnit;
    
    float                   _ropeRadius;
};

#endif // __Rope_H__
