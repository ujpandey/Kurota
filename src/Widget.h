#ifndef WIDGET_H
#define WIDGET_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "TextureManager.h"
#include "Game.h"

class Widget
{
public:
    virtual ~Widget(){}
    
    virtual void draw(SDL_Renderer * renderer);
    virtual void update();
    virtual void add_child(Widget * widget);
    virtual void remove_child(Widget * widget);
    virtual const SDL_Rect * get_bounds() = 0;
    
protected:
    Widget(const std::string & id);
    
private:
    std::string _id;
};

class Button : Widget
{
public:
    Button(const std::string & id,
           int x, int y, int w, int h);
    virtual ~Button(){}

    virtual void draw(SDL_Renderer * renderer);
    virtual void update();
    
private:
    SDL_Rect _bounding_rect;
    SDL_Color 
};

class CompositeWidget : public Widget
{
public:
    virtual ~CompositeWidget();

    virtual void draw(SDL_Renderer * renderer);
    virtual void update();
    virtual void add_child(Widget *);
    virtual void remove_child(Widget *);
    virtual const SDL_Rect * get_bounds() = 0;

protected:
    CompositeWidget(const std::string & id);
    
private:
    std::vector< Widget * > _widgets;
};

class DecoratorWidget : public Widget
{
public:
    virtual ~DecoratorWidget();

    virtual void draw(SDL_Renderer * renderer);
    virtual void update();
    virtual void add_child(Widget *);
    virtual void remove_child(Widget *);
    virtual const SDL_Rect * get_bounds() = 0;

protected:
    DecoratorWidget(const std::string & id);

private:
    Widget * _widget;
};

class DialogueBox : public CompositeWidget
{
public:
};

#endif
