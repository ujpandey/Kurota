#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Includes.h"
#include "EventHandler.h"
#include "Vec2.h"
#include "Timer.h"

class GameObject : public EventHandler
{
public:
    virtual void draw(SDL_Renderer * renderer) const = 0;
    virtual void update() = 0;
protected:
    GameObject(const std::string & id)
        : EventHandler(id)
    {}
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

    void on_mouse_button_down();

    void respawn();
    
    std::string serialize() const;
    void deserialize(const std::string & serialized);

protected:
    std::string _password;
    vec2d _position;
    int _w, _h;
    int _hp, _mana;
    vec2d _velocity;
    vec2d _acceleration;
    vec2d _target_position;
    Direction _facing;
    bool _moving;
    Timer _timer;
//    Animation * _animation;
};

class RemotePlayer : public Player
{
public:
    RemotePlayer(const std::string & id,
                 const std::string & texture_file,
                 SDL_Renderer * renderer,
                 int x=0, int y=0, int w=64, int h=64);
    
    void on_mouse_button_down();
    std::string serialize() const;
    void on_ntwk_update(const std::string & netstr);
};

#endif
