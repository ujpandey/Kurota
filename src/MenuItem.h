#ifndef MENUITEM_H
#define MENUITEM_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "TextureManager.h"
#include "Game.h"

class MenuItem
{
public:
    virtual ~MenuItem(){}
    
    virtual void draw(SDL_Renderer * renderer);
    virtual void update();
    virtual void add_child(MenuItem * menu_item);
    virtual void remove_child(MenuItem * menu_item);
    virtual const SDL_Rect get_bounds();
    
protected:
    MenuItem(const std::string & id,
             int x, int y, int w, int h);
    
private:
    std::string _id;
    int _x, _y, _w, _h;
};

class Button : MenuItem
{
public:
    Button(const std::string & id,
           int x, int y, int w, int h,
           const std::string & texture_file);
    virtual ~Button(){}

    virtual void draw(SDL_Renderer * renderer);
    virtual void update();
}

class CompositeMenuItem : public MenuItem
{
public:
    virtual ~CompositeMenuItem();

    virtual void draw(SDL_Renderer * renderer);
    virtual void update();
    virtual void add_child(MenuItem *);
    virtual void remove_child(MenuItem *);

protected:
    CompositeMenuItem(const std::string & id)
        : MenuItem(id)
    {}
private:
    std::vector< MenuItem * > _menu_items;
};

class DialogueBox : public CompositeMenuItem
{
public:
};

#endif
