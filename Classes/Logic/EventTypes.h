#ifndef __EventTypes_H__
#define __EventTypes_H__

enum EventType
{
    EventNone           = -1,
    EventCreateUnit     = 1,
    EventMax            = 1,
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

#endif // __EventTypes_H__
