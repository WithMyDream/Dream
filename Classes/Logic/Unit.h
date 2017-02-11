#ifndef __Unit_H__
#define __Unit_H__

#include "base/CCRef.h"
#include "Box2D/Box2D.h"

class World;

class Unit : public cocos2d::Ref
{
public:
    static Unit* create(World* world, int ID);
    
    Unit();
    ~Unit();
    bool init(World* world, int ID);
    
    void createB2Body();
    b2Body* getB2Body(){ return _b2Body; }

    void setPosition(b2Vec2 &pos);
    const b2Vec2& getPostion();
    
    void setAngle(float32 angle);
    float32 getAngle();
    
    void move(float angle);
    void jump();
    
    void update(float dt);
    
private:
    void _move();
    
private:
    World*      _world; // weak ref
    b2Body*     _b2Body;
    
    int         _ID;
    
    float       _delta;
    
    // jump
    b2Vec2      _jumpImpulseMax;
    
    // move
    float       _moveVxMax;
    float       _moveAngle;
    b2Vec2      _currMoveForce;
    int         _currDir;
};

#endif // __Unit_H__
