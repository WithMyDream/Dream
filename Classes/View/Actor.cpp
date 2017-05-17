#include "Actor.h"

Actor* Actor::create(Unit* unit)
{
    Actor* actor = new Actor();
    if (actor && actor->init(unit)) {
        actor->autorelease();
    }
    return actor;
}

Actor::Actor()
:_unit(nullptr)
, _isDestroy(false)
{
    
}

Actor::~Actor()
{
	CCLOG("Actor::~Actor");
    _unit = nullptr;
}

bool Actor::init(Unit* unit)
{
	_unit = unit;
	if (_unit)
	{
		switch (_unit->getType())
		{
		case UnitTypeHero:

			break;
		case UnitTypeRope:

			break;
		case UnitTypeGround:
		{
			Color4B color(255, 255, 255, 255);
			const b2Vec2& size = unit->getSize();
			LayerColor* layerColor = LayerColor::create(color, size.x*B2SCALE, size.y*B2SCALE);
            layerColor->setPosition(-size.x*B2SCALE/2.0f, -size.y*B2SCALE/2.0f);
			addChild(layerColor);
			break;
		}
		default:
			CCLOG("No need to init the unit type : %d", _unit->getType());
			break;
		}
	}
    
    return true;
}

void Actor::end()
{

}

void Actor::update(float dt)
{   
    if (!_unit)
        return;
    
    const b2Vec2& pos = _unit->getPostion();
    setPosition(pos.x*B2SCALE, pos.y*B2SCALE);
    setRotation(CC_RADIANS_TO_DEGREES(_unit->getAngle() * -1.0f));
}
