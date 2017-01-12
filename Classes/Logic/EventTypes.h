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
    virtual ~EventParams();
    
    EventType _eventType;
};

class ECreateUnit : public EventParams
{
public:
    ECreateUnit(int ID):EventParams(EventCreateUnit)
    ,_ID(ID)
    {};
    ~ECreateUnit();
    
    int _ID;
};

#endif // __EventTypes_H__
