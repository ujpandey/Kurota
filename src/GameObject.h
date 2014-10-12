#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include <string>

#include "TextureManager.h"
#include "Game.h"

class GameObject
{
public:
    virtual void draw(SDL_Renderer * renderer) = 0;
    virtual void update() = 0;
};

class Player : public GameObject
{
public:
    Player(const std::string & id,
           const std::string & texture_file,
           SDL_Renderer * renderer,
           int x=0, int y=0, int w=64, int h=64);
    void draw(SDL_Renderer * renderer);
    void update();

private:
    std::string id;
    int x, y, w, h;
};

#endif
