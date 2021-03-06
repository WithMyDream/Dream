#ifndef __Actor_H__
#define __Actor_H__

#include "cocos2d.h"
#include "../Logic/Unit.h"
#include "../Logic/World.h"

using namespace cocos2d;

class Actor : public Node
{
public:
    static Actor* create(Unit* unit);
    
    Actor();
    ~Actor();
    bool init(Unit* unit);
	void end();
	void destroy() { _isDestroy = true; }
	bool isDestroy() const { return _isDestroy; }
    
	Unit* getUnit() { return _unit; }
    
    void update(float dt);
    
private:
    
    
private:
    Unit*	_unit;    // weak ref
	bool	_isDestroy;
};

#endif // __Actor_H__
