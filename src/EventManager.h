#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "Includes.h"
#include "EventHandler.h"

class EventManager
{
public:
    static EventManager * get_instance();
    void lease(EventHandler * e_h);
    void release(EventHandler * e_h);
    void coup(EventHandler * e_h);
    void pop();
    void clear();
    void handle_event();

protected:
    EventManager(){}

private:
    static EventManager * instance;
    std::vector< EventHandler * > event_handlers;
    SDL_Event _event;
};

#endif
