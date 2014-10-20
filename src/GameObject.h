#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

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
    
class GameObject : public EventHandler
{
public:
    virtual void draw(SDL_Renderer * renderer) const = 0;
    virtual void update() = 0;
};

class Player : public GameObject
{
public:
    Player(const std::string & id,
           const std::string & texture_file,
           SDL_Renderer * renderer,
           int x=0, int y=0, int w=64, int h=64);
    void draw(SDL_Renderer * renderer) const;
    void update();
    std::string serialize() const;

private:
    std::string _id;
    int _x, _y, _w, _h;
};

#endif
