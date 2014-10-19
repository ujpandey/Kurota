#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "Game.h"

enum MouseButtons { LEFT, MIDDLE, RIGHT };
    
class EventHandler
{
public:
    static EventHandler * get_instance();
    void update();
    void on_mouse_move(SDL_Event & event);
    void on_mouse_button_down(SDL_Event & event);
    void on_mouse_button_up(SDL_Event & event);
    void on_key_down();
    void on_key_up();    

protected:
    EventHandler(){}

private:
    static EventHandler * instance;
    int mouse_button_states[3];
};

#endif
