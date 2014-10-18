#ifndef TEXT_H
#define TEXT_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Game.h"
#include "TextureManager.h"

class Glyph : public GameObject
{
public:
    virtual ~Glyph();

    virtual void draw(SDL_Renderer * renderer) const;
    virtual void update();
    virtual void add_child(Glyph * glyph);
    virtual void remove_child(Glyph * glyph);
}
