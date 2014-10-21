#ifndef WIDGET_H
#define WIDGET_H

#include "Game.h"
#include "TextureManager.h"

class Widget : public GameObject
{
public:
    virtual ~Widget();
    
    virtual void draw(SDL_Renderer * renderer) const;
    virtual void update();
    virtual const SDL_Rect * get_bounds() const = 0;
    
protected:
    Widget(const std::string & id);
};

class Button : public Widget
{
public:
    Button(const std::string & id,
           const std::string & texture_file,
           SDL_Renderer * renderer,
           int x=0, int y=0, int w=0, int h=0);
    virtual ~Button();

    virtual void draw(SDL_Renderer * renderer) const;
    virtual void update();
    virtual const SDL_Rect * get_bounds() const;
    
private:
    SDL_Rect _bounding_rect;
};

class CompositeWidget : public Widget
{
public:
    virtual ~CompositeWidget();

    virtual void draw(SDL_Renderer * renderer) const;
    virtual void update();
    virtual void add_child(Widget *);
    virtual void remove_child(Widget *);
    virtual const SDL_Rect * get_bounds() const = 0;

protected:
    CompositeWidget(const std::string & id);
    std::vector< Widget * > _widgets;
};

class DialogBox : public CompositeWidget
{
public:
    DialogBox(const std::string & id,
              const std::string & bg_texture_file,
              SDL_Renderer * renderer,
              int x=0, int y=0, int w=0, int h=0);
    virtual ~DialogBox();
    virtual void update();
    virtual void add_child(Widget *);
    virtual void remove_child(Widget *);
    virtual const SDL_Rect * get_bounds() const;

private:
    // int _padding; // Gonna assume atomic widgets know their placement.
    // Direction _add_dir; // Switch to strategy pattern sometime ????
    SDL_Rect _bounding_rect;
};

class DecoratorWidget : public Widget
{
public:
    virtual ~DecoratorWidget();

    virtual void draw(SDL_Renderer * renderer) const;
    virtual void update();
    virtual void add_child(Widget *);
    virtual void remove_child(Widget *);
    virtual const SDL_Rect * get_bounds() const = 0;

protected:
    DecoratorWidget(const std::string & id);
    Widget * _widget;
};

class Border : public DecoratorWidget
{
public:
    Border(const std::string & id, int width,
           Uint8 r, Uint8 g, Uint8 b, Uint8 a);
           
    virtual ~Border();

    virtual void draw(SDL_Renderer * renderer) const;
    virtual void update();
    virtual void add_child(Widget *);
    virtual void remove_child(Widget *);
    virtual const SDL_Rect * get_bounds() const;
    
private:
    int _width;
    SDL_Color _color;
    SDL_Rect _bounding_rect;
};

#endif
