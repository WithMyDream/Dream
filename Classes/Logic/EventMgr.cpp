#include "EventMgr.h"

static EventMgr* _eventManager = nullptr;

EventMgr* EventMgr::getInatence()
{
    if (!_eventManager) {
        _eventManager = new EventMgr();
        _eventManager->init();
    }
    return _eventManager;
}

void EventMgr::destory()
{
    if (!_eventManager) {
        return;
    }
    delete _eventManager;
    _eventManager = nullptr;
}

EventMgr::EventMgr()
{
    
}

EventMgr::~EventMgr()
{
    for (int i=0; i<EventMax; ++i) {
        delete _eventManager->_eventHandlers.at(i);
    }
}

void EventMgr::init()
{
    _eventHandlers.resize(EventMax);
    for (int i=0; i<EventMax; ++i) {
        _eventHandlers.push_back(new std::list<EventHandler>());
    }
}

void EventMgr::registerEvent(EventType eventType, EventHandler eventHandler)
{
    if (eventType > EventMax) {
        CCLOG("There is not this event %d", eventType);
        return;
    }
    
    _eventHandlers.at(eventType)->push_back(eventHandler);
}

void EventMgr::unregisterHandler(EventHandler eventHandler)
{
//    for (int i=0; i<EventMax; ++i) {
//        std::list<EventHandler>* handles = _eventHandlers.at(i);
//        std::list<EventHandler>::iterator it = std::find(handles->begin(), handles->end(), eventHandler);
//        if (it != handles->end())
//            handles->erase(it);
//    }
}

void EventMgr::unregisterEvent(EventType eventType)
{
    _eventHandlers.at(eventType)->clear();
}

void EventMgr::notify(EventParams &params)
{
    std::list<EventHandler>* handles = _eventHandlers.at(params._eventType);
    std::list<EventHandler>::iterator it = handles->begin();
    for (; it != handles->end(); ++it) {
        (*it)(params);
    }
}
