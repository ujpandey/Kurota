#include "Widget.h"
#include "Game.h"
#include "TextureManager.h"
#include "EventManager.h"
#include "Command.h"

//-----------------------------------------------------------------------------
// Widget
//-----------------------------------------------------------------------------
Widget::Widget(const std::string & id)
    : GameObject(id)
{}

Widget::~Widget()
{}

void Widget::draw(SDL_Renderer * renderer) const
{
    SDL_RenderDrawRect(renderer, get_bounds());
}

void Widget::update()
{
}


//-----------------------------------------------------------------------------
// Button
//-----------------------------------------------------------------------------
Button::Button(const std::string & id,
               const std::string & texture_file,
               SDL_Renderer * renderer,
               int x, int y, int w, int h,
               Command * command)
    : Widget(id), _command(command)
{
    _bounding_rect.x = x;
    _bounding_rect.y = y;
    if (w && h)
    {
        _bounding_rect.w = w;
        _bounding_rect.h = h;
    }
    else
    {
        SDL_Surface * tmp = IMG_Load(texture_file.c_str());
        _bounding_rect.w = tmp -> w;
        _bounding_rect.h = tmp -> h;
        SDL_FreeSurface(tmp);
    }
    TextureManager::get_instance() -> load(texture_file, id, renderer);
}

Button::~Button()
{}

void Button::on_mouse_button_down()
{
    vec2d _mouse_position = EventManager::get_instance() -> get_mouse_position();
    SDL_Point p = {_mouse_position.get_x(), _mouse_position.get_y()};
    if (SDL_PointInRect(&p, get_bounds()))
    {
        if (_command)
        {
            _command -> execute();
        }
    }
    else
        _successor -> on_mouse_button_down();
}

void Button::draw(SDL_Renderer * renderer) const
{
    TextureManager::get_instance() ->
        render(_id, 0, 0, _bounding_rect.w, _bounding_rect.h,
               _bounding_rect.x, _bounding_rect.y,
               _bounding_rect.w, _bounding_rect.h, renderer);
}

void Button::update()
{
}

const SDL_Rect * Button::get_bounds() const
{
    return &_bounding_rect;
}

void Button::set_bounds(const int & x,
                        const int & y,
                        const int & w,
                        const int & h)
{
    _bounding_rect.x = x;
    _bounding_rect.y = y;
    _bounding_rect.w = w;
    _bounding_rect.h = h;
}


//-----------------------------------------------------------------------------
// CompositeWidget
//-----------------------------------------------------------------------------
CompositeWidget::CompositeWidget(const std::string & id)
    : Widget(id)
{}

CompositeWidget::~CompositeWidget()
{
    for (std::vector< Widget * >::iterator it = _widgets.begin();
         it != _widgets.end(); ++it)
    {
        delete (*it);
    }
}

void CompositeWidget::draw(SDL_Renderer * renderer) const
{
    const SDL_Rect * brect = get_bounds();
    TextureManager::get_instance() ->
        render(_id, 0, 0, brect -> w, brect -> h,
               brect -> x, brect -> y, brect -> w, brect -> h, renderer);

    // SDL_RenderSetViewport(Game::get_instance() -> get_renderer(), brect);
    for (std::vector< Widget * >::const_iterator it = _widgets.begin();
         it != _widgets.end(); ++it)
    {
        (*it) -> draw(renderer);
    }
    //SDL_RenderSetViewport(Game::get_instance() -> get_renderer(), NULL);
}

void CompositeWidget::update()
{
    for (std::vector< Widget * >::const_iterator it = _widgets.begin();
         it != _widgets.end(); ++it)
    {
        (*it) -> update();
    }
}

void CompositeWidget::add_child(Widget * widget)
{
    const SDL_Rect * brect = get_bounds();
    const SDL_Rect * child_brect = widget -> get_bounds();
    widget -> set_bounds(brect -> x + child_brect -> x,
                         brect -> y + child_brect -> y,
                         child_brect -> w,
                         child_brect -> h);
    EventManager::get_instance() -> release(this);
    EventManager::get_instance() -> lease(widget);
    widget -> set_successor(this);
    _widgets.push_back(widget);
}

void CompositeWidget::remove_child(Widget * widget)
{
    std::vector< Widget * >::iterator it =
        std::find(_widgets.begin(), _widgets.end(), widget);
    if (it != _widgets.end())
        _widgets.erase(it);   
}


//-----------------------------------------------------------------------------
// DialogBox
//-----------------------------------------------------------------------------
DialogBox::DialogBox(const std::string & id,
                     const std::string & bg_texture_file,
                     SDL_Renderer * renderer,
                     int x, int y, int w, int h)
    : CompositeWidget(id)
{
    _bounding_rect.x = x;
    _bounding_rect.y = y;
    _bounding_rect.w = w;
    _bounding_rect.h = h;
    
    TextureManager::get_instance() -> load(bg_texture_file, id, renderer); 
}

DialogBox::~DialogBox()
{}

void DialogBox::update()
{
    for (std::vector< Widget * >::const_iterator it = _widgets.begin();
         it != _widgets.end(); ++it)
    {
        (*it) -> update();
    }
}

// Gonna assume we won't be doing any auto sizing etc.
void DialogBox::add_child(Widget * widget)
{
    /*
    SDL_Rect tmp = _bounding_rect;
    switch(_auto_add_dir)
    {
        case NORTH:
        case SOUTH:
            tmp.h += _padding;
            break;
        case EAST:
        case WEST:
            tmp.w += _padding;
    }
    

    const SDL_Rect * child = widget -> get_bounds();
    
    _bounding_rect.w += child -> w + (child -> x - _bounding_rect.w) + 10;
    _bounding_rect.h += child -> h + (child -> y - _bounding_rect.h) + 10;
    */
    const SDL_Rect * brect = get_bounds();
    const SDL_Rect * child_brect = widget -> get_bounds();
    widget -> set_bounds(brect -> x + child_brect -> x,
                         brect -> y + child_brect -> y,
                         child_brect -> w,
                         child_brect -> h);
    EventManager::get_instance() -> release(this);
    EventManager::get_instance() -> lease(widget);
    widget -> set_successor(this);
    _widgets.push_back(widget);
}

void DialogBox::remove_child(Widget * widget)
{
    // Resize on remove???
    std::vector< Widget * >::iterator it =
        std::find(_widgets.begin(), _widgets.end(), widget);
    if (it != _widgets.end())
        _widgets.erase(it);
}

const SDL_Rect * DialogBox::get_bounds() const
{
    return &_bounding_rect;
}

void DialogBox::set_bounds(const int & x,
                        const int & y,
                        const int & w,
                        const int & h)
{
    _bounding_rect.x = x;
    _bounding_rect.y = y;
    _bounding_rect.w = w;
    _bounding_rect.h = h;
}


//-----------------------------------------------------------------------------
// DecoratorWidget
//-----------------------------------------------------------------------------
DecoratorWidget::DecoratorWidget(const std::string & id)
    : Widget(id)
{}

DecoratorWidget::~DecoratorWidget()
{
    delete _widget;
}

void DecoratorWidget::draw(SDL_Renderer * renderer) const
{
    _widget -> draw(renderer);
    SDL_RenderDrawRect(renderer, get_bounds());
}

void DecoratorWidget::update()
{
    _widget -> update();
}

void DecoratorWidget::add_child(Widget * widget)
{
    EventManager::get_instance() -> release(this);
    EventManager::get_instance() -> lease(widget);
    widget -> set_successor(this);
    _widget = widget;
}

void DecoratorWidget::remove_child(Widget * widget)
{
    _widget = NULL;
}


//-----------------------------------------------------------------------------
// Border
//-----------------------------------------------------------------------------
Border::Border(const std::string & id, int width,
               Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    : DecoratorWidget(id), _width(width)
{
    _color.r = r;
    _color.g = g;
    _color.b = b;
    _color.a = a;
}

Border::~Border()
{
}

void Border::draw(SDL_Renderer * renderer) const
{
    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    SDL_SetRenderDrawColor(renderer, _color.r, _color.g, _color.b, _color.a);
    SDL_RenderFillRect(renderer, get_bounds());
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    _widget -> draw(renderer);
}

void Border::update()
{
    _widget -> update();
}

void Border::add_child(Widget * widget)
{
    const SDL_Rect * tmp = widget -> get_bounds();
    std::cout << tmp -> x << ' ' << tmp -> y << ' ' << tmp -> w << ' ' << tmp -> h << std::endl;
    _bounding_rect.x = tmp -> x - _width;
    _bounding_rect.y = tmp -> y - _width;
    _bounding_rect.w = tmp -> w + _width + _width;
    _bounding_rect.h = tmp -> h + _width + _width;
    const SDL_Rect * br = &_bounding_rect;
    std::cout << br -> x << ' ' << br -> y << ' ' << br -> w << ' ' << br -> h << std::endl;
    EventManager::get_instance() -> release(this);
    EventManager::get_instance() -> lease(widget);
    widget -> set_successor(this);
    _widget = widget;
}

void Border::remove_child(Widget * widget)
{
    _widget = NULL;
}

const SDL_Rect * Border::get_bounds() const
{
    return &_bounding_rect;
}

void Border::set_bounds(const int & x,
                        const int & y,
                        const int & w,
                        const int & h)
{
    _bounding_rect.x = x;
    _bounding_rect.y = y;
    _bounding_rect.w = w;
    _bounding_rect.h = h;
}

