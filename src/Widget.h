#ifndef WIDGET_H
#define WIDGET_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "Game.h"
#include "TextureManager.h"

class Widget : public GameObject
{
public:
    virtual ~Widget();
    
    virtual void draw(SDL_Renderer * renderer) const;
    virtual void update();
    virtual void add_child(Widget * widget);
    virtual void remove_child(Widget * widget);
    virtual const SDL_Rect * get_bounds() const = 0;
    
protected:
    Widget(const std::string & id);
    std::string _id;
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
    virtual const SDL_Rect * get_bounds() const;

private:
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

private:
    Widget * _widget;
};

#endif
