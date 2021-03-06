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
            const std::string & text="",
            int x=0, int y=0, int w=0, int h=0, bool password=false);
    ~TextBox();
    
    virtual void draw(SDL_Renderer * renderer) const;
    virtual void on_mouse_button_down();
    virtual void on_key_down();
    virtual void on_text_input();
    virtual void update();
    virtual const SDL_Rect * get_bounds() const;
    virtual void set_bounds(const int & x,
                            const int & y,
                            const int & w,
                            const int & h);
    virtual void set_focus();
    virtual const std::string & get_text() const;
    
private:
    std::string _text;
    bool _focus;
    bool _redraw;
    bool _maxed;
    bool _password;
    SDL_Color _bgcolor;
    SDL_Color _textcolor;
    SDL_Rect _bounding_rect; 
};

class TextArea : public Widget
{
public:
    TextArea(const std::string & id,
            const std::string & text="",
            int x=0, int y=0, int w=0, int h=0);
    ~TextArea();
    
    virtual void draw(SDL_Renderer * renderer) const;
    virtual void update();
    virtual const SDL_Rect * get_bounds() const;
    virtual void set_bounds(const int & x,
                            const int & y,
                            const int & w,
                            const int & h);
    virtual void set_text(const std::string & text);
private:
    std::string _text;
    bool _redraw;
    SDL_Color _textcolor;
    SDL_Rect _bounding_rect;
};

#endif
