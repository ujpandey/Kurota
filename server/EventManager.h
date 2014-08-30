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
    
    const vec2d & get_mouse_position() const;

    const bool & get_mouse_button_state(MouseButton button) const;

    const SDL_Event & get_event() const;

protected:
    EventManager();

private:
    void update_mpos();
    void update_mbstates_mdown();
    void update_mbstates_mup();
    
    static EventManager * instance;
    SDL_Event _event;
    bool _mouse_button_states[3];
    vec2d _mouse_position;
    std::vector< EventHandler * > event_handlers;
};

#endif
