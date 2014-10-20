#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "Game.h"
#include "Vec2.h"

enum MouseButton { LEFT, MIDDLE, RIGHT };
    
class EventHandler
{
public:
    static EventHandler * get_instance();
    
    void update();
    
    const vec2d & get_mouse_position() const;

    bool get_mouse_button_state(MouseButton button) const;

    bool is_key_down(SDL_Scancode key);

protected:
    EventHandler();
    
private:
    void on_mouse_move(SDL_Event & event);
    void on_mouse_button_down(SDL_Event & event);
    void on_mouse_button_up(SDL_Event & event);
    
    void on_key_down();
    void on_key_up();
    
    static EventHandler * instance;
    bool mouse_button_states[3];
    vec2d mouse_position;
    const Uint8 * key_states;
};

#endif
