#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "Includes.h"

enum MouseButton { LEFT, MIDDLE, RIGHT };
    
class EventHandler
{
public:
    virtual ~EventHandler();

    virtual void on_quit();
    
    virtual void on_mouse_move();
    virtual void on_mouse_button_down();
    virtual void on_mouse_button_up();
    
    virtual void on_key_down();
    virtual void on_key_up();

    virtual void on_text_input();

    void handle_event();
    virtual void update() = 0;

    void set_successor(EventHandler * successor);

    const std::string & get_id() const;

protected:
    EventHandler(const std::string & id);
    std::string _id;
    EventHandler * _successor;
};

#endif
