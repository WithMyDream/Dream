#ifndef __EventMgr_H__
#define __EventMgr_H__

#include "EventTypes.h"
#include <vector>

#define REGISTER_EVENT(eventType, classFunc) \
    EventHandler handler = [this](EventParams& params) \
    { \
        CCLOG("EventHandler ~~~~ "); \
        this->classFunc(params); \
    }; \
    EventMgr::getInatence()->registerEvent(eventType, handler); \

#define UNREGISTER_EVENT(handler) EventMgr::getInatence()->unregisterHandler(handler);

typedef std::function<void(EventParams&)> EventHandler;

class EventMgr
{
public:
    static EventMgr* getInatence();
    static void destory();
    
    EventMgr();
    ~EventMgr();
    void init();
    
    void registerEvent(EventType eventType, EventHandler handler);
    void unregisterHandler(EventHandler handler);
    void unregisterEvent(EventType eventType);
    
    void notify(EventParams &params);
private:
    std::vector<std::list<EventHandler>*> _eventHandlers;
};

#endif // __EventMgr_H__
