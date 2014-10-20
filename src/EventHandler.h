#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include "Game.h"

#include "Vec2.h"

enum MouseButton { LEFT, MIDDLE, RIGHT };
    
class EventHandler
{
public:
    virtual ~EventHandler();
    
    virtual void on_mouse_move();
    virtual void on_mouse_button_down();
    virtual void on_mouse_button_up();
    
    virtual void on_key_down();
    virtual void on_key_up();

    virtual void on_text_input();

    void handle_event();
    virtual void update() = 0;
    
    const vec2d & get_mouse_position() const;

    bool get_mouse_button_state(MouseButton button) const;

    void set_successor(EventHandler * successor);

protected:
    EventHandler();
    static SDL_Event _event;
    static bool _mouse_button_states[3];
    static vec2d _mouse_position;
    EventHandler * _successor;
    
private:
    void update_mpos();
    void update_mbstates_mdown();
    void update_mbstates_mup();
};

#endif
