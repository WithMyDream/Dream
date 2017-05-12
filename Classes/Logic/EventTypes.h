#ifndef __EventTypes_H__
#define __EventTypes_H__

enum EventType
{
    EventCreateUnit = 0,
	EventCreateRope,
	EventDestroyUnit,
	EventSetMainUnit,
    EventJoystick,
    EventButton,
    EventMax,
};

class EventParams
{
public:
    EventParams(EventType eventType):_eventType(eventType){};
    
    EventType _eventType;
};

class Unit;
class ECreateUnit : public EventParams
{
public:
    ECreateUnit(Unit* unit):EventParams(EventCreateUnit)
    ,_unit(unit)
    {};
    
    Unit* _unit;
};

class Rope;
class ECreateRope : public EventParams
{
public:
	ECreateRope(Rope* rope):EventParams(EventCreateRope)
	, _rope(rope)
	{};

	Rope* _rope;
};

class EDestroyUnit : public EventParams
{
public:
	EDestroyUnit(Unit* unit):EventParams(EventDestroyUnit)
	, _unit(unit)
	{};

	Unit* _unit;
};

class ESetMainUnit : public EventParams
{
public:
	ESetMainUnit(Unit* unit) :EventParams(EventSetMainUnit)
		, _unit(unit)
	{};

	Unit* _unit;
};

class EJoystick : public EventParams
{
public:
    EJoystick(float angle):EventParams(EventJoystick)
    ,_angle(angle)
    {};
    
    float _angle;
};

class EButton : public EventParams
{
public:
    EButton(int index):EventParams(EventButton)
    ,_index(index)
    {};
    
    int _index;
};

#endif // __EventTypes_H__
