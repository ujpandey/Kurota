#include "EventManager.h"

EventManager * EventManager::instance = NULL;

EventManager * EventManager::get_instance()
{
    if (instance)
        return instance;
    instance = new EventManager;
    return instance;
}

void EventManager::lease(EventHandler * e_h)
{
    event_handlers.push_back(e_h);
}

void EventManager::release(EventHandler * e_h)
{
    std::vector< EventHandler * >::iterator it =
        std::find(event_handlers.begin(), event_handlers.end(), e_h);
    if (it != event_handlers.end())
        event_handlers.erase(it);
}

void EventManager::coup(EventHandler * e_h)
{
    event_handlers.push_back(e_h);
}

void EventManager::pop()
{
    event_handlers.pop_back();
}

void EventManager::clear()
{
    event_handlers.clear();
}

void EventManager::handle_event()
{
    while (SDL_PollEvent(&_event))
    {
        EventHandler::register_event(&_event);
        for (std::vector< EventHandler * >::reverse_iterator rit =
                 event_handlers.rbegin(); rit != event_handlers.rend(); ++rit)
        {
            (*rit) -> handle_event();
        }
    }
}

