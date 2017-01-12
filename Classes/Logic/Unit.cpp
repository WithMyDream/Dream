#include "Unit.h"

Unit* Unit::create()
{
    Unit* unit = new Unit();
    if (unit && unit->init()) {
        unit->autorelease();
    }
    return unit;
}

Unit::Unit()
:_b2Body(nullptr)
{
    
}

Unit::~Unit()
{
    
}

bool Unit::init()
{
    
    
    return true;
}

void Unit::update(float dt)
{
    
}
