#include "MenuItem.h"

//-----------------------------------------------------------------------------
// MenuItem
//-----------------------------------------------------------------------------
MenuItem(const std::string & id,
         int x, int y, int w, int h)
    : _id(id), _x(x), _y(y), _w(w), _h(h)
{}

void MenuItem::draw(SDL_Renderer * renderer)
{
    SDL_RenderDrawRect(renderer, get_bounds());
}

void MenuItem::update()
{
}

void MenuItem::add_child(MenuItem * menu_item)
{
    std::cerr << "Basic menu items can't have children." << std::endl;
}

void MenuItem::remove_child(MenuItem * menu_item)
{
    std::cerr << "Basic menu items can't have children." << std::endl;
}

const SDL_Rect MenuItem::get_bounds()
{
    SDL_Rect ret;
    ret.x = _x;
    ret.y = _y;
    ret.w = _w;
    ret.h = _h;
    
    return ret;
}

//-----------------------------------------------------------------------------
// CompositeMenuItem
//-----------------------------------------------------------------------------
CompositeMenuItem(const std::string & id,
                  int x, int y, int w, int h)
    : MenuItem(id, x, y, w, h)
{}

void CompositeMenuItem::draw(SDL_Renderer * renderer)
{
    for (std::vector< MenuItem * >::iterator it = _menu_items.begin();
         it != _menu_items.end(); ++it)
    {
        
    }
    
    SDL_RenderDrawRect(renderer, get_bounds());
}

void CompositeMenuItem::update()
{
}

void CompositeMenuItem::add_child(MenuItem * menu_item)
{
    _menu_items.push_back(menu_item);
}

void CompositeMenuItem::remove_child(MenuItem * menu_item)
{
    std::vector< MenuItem * >::iterator it =
        std::find(_menu_items.begin(), _menu_items.end(), menu_item);
    if (it != _menu_items.end())
        _menu_items.erase(it);
}

const SDL_Rect CompositeMenuItem::get_bounds()
{
    SDL_Rect ret;
    ret.x = _x;
    ret.y = _y;
    ret.w = _w;
    ret.h = _h;
    
    return ret;
}
