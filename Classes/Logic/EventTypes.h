#ifndef __EventTypes_H__
#define __EventTypes_H__

enum EventType
{
    EventCreateUnit = 0,
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
