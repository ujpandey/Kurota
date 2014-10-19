#ifndef TEXT_H
#define TEXT_H

#include "Widget.h"

/*
// Not sure about SDL's implementation regarding it's weight.
// Try flyweight sometime just for kicks.
class Glyph : public GameObject
{
public:
    virtual ~Glyph();

    virtual void draw(SDL_Renderer * renderer) const;
    virtual void update();
    virtual void add_child(Glyph * glyph);
    virtual void remove_child(Glyph * glyph);
}
*/


class TextBox : public Widget
{
public:
    TextBox(const std::string & id,
            const std::string & font_file,
            SDL_Renderer * renderer,
            int x=0, int y=0, int w=0, int h=0,
            const std::string & text);
}
