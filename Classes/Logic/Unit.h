#ifndef __Unit_H__
#define __Unit_H__

#include "base/CCRef.h"
#include "Box2D/Box2D.h"
#include <string>

class World;
class Rope;

enum UnitType
{
	UnitTypeUnknown,
	UnitTypeHero,
	UnitTypeJoint,
	UnitTypeGround,
	UnitTypeBarrier,
	UnitTypeFrame
};

class Unit : public cocos2d::Ref
{
public:
    static Unit* create(World* world, int ID);
    
    Unit();
    ~Unit();
    virtual bool init(World* world, int ID);
    virtual void end();
	void destroy() { _isDestroy = true; }
	bool isDestroy() const { return _isDestroy; }
    
    virtual void initB2Body();
    virtual b2Body* getB2Body(){ return _b2Body; }

    virtual void setPosition(b2Vec2 &pos);
    virtual const b2Vec2& getPostion();
    
    virtual void setAngle(float32 angle);
    virtual float32 getAngle();

	void setIndex(int index) { _index = index; }
	int getIndex() { return _index; }

	int getID() { return _ID; }

	void setName(std::string& name) { _name = name; }
	std::string getName() { return _name; }

	void setType(UnitType type) { _type = type; }
	UnitType getType() { return _type; }
    
    void move(float angle);
    void jump();
    void hang(Unit* unit);
    
    virtual void update(float dt);
    
protected:
    void _move();
    
protected:
    World*      _world; // weak ref
    b2Body*     _b2Body;
	bool		_isDestroy;
    
	int			_index;
    int         _ID;
	std::string	_name;
	UnitType	_type;
	
    float       _delta;
	
    // move
    float       _moveVxMax;
    float       _moveAngle;
    b2Vec2      _currMoveForce;
    int         _currDir;

	// jump
	b2Vec2      _jumpImpulseMax;

	// hang
	Rope*		_linkingRope;
    Unit*       _linkingJoint;
};

#endif // __Unit_H__
