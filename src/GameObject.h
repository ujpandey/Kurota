#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "Game.h"
    
class GameObject
{
public:
    GameObject(){}
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
