#ifndef __Rope_H__
#define __Rope_H__

#include "Unit.h"

class Rope : public Unit
{
public:
    static Rope* create(World* world, int ID);
    
    Rope();
    ~Rope();
    bool init(World* world, int ID) override;
    
    void initB2Body() override;
    b2Body* getB2Body() override { return getFirstBody(); }
    
    void addOneBody();
    std::vector<b2Body*>& getB2Bodies(){ return _b2Bodies; }
    b2Body* getFirstBody(){ return _b2Bodies.front(); }
    b2Body* getLastBody(){ return _b2Bodies.back(); }
    void jointFirstTo(Unit* unit);
    void jointLastTo(Unit* unit);

    void setPosition(b2Vec2 &pos) override;
    const b2Vec2& getPostion() override;
    
    void setAngle(float32 angle) override;
    float32 getAngle() override;
    
    void setRopeRadius(float ropeRadius);
    
    void update(float dt) override;
    
private:
    
    
private:
    std::vector<b2Body*>    _b2Bodies;
    std::vector<b2Joint*>   _b2Joints;
    
    float                   _ropeRadius;
};

#endif // __Rope_H__
