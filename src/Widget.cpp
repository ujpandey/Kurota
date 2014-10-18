#include "Widget.h"


//-----------------------------------------------------------------------------
// Widget
//-----------------------------------------------------------------------------
Widget::Widget(const std::string & id)
    : _id(id)
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

void Widget::add_child(Widget * widget)
{
    std::cerr << "Basic menu items can't have children." << std::endl;
}

void Widget::remove_child(Widget * widget)
{
    std::cerr << "Basic menu items can't have children." << std::endl;
}


//-----------------------------------------------------------------------------
// Button
//-----------------------------------------------------------------------------
Button::Button(const std::string & id,
               const std::string & texture_file,
               SDL_Renderer * renderer,
               int x, int y, int w, int h)
    : Widget(id)
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

    SDL_RenderSetViewport(Game::get_instance() -> get_renderer(), brect);
    for (std::vector< Widget * >::const_iterator it = _widgets.begin();
         it != _widgets.end(); ++it)
    {
        (*it) -> draw(renderer);
    }
    SDL_RenderSetViewport(Game::get_instance() -> get_renderer(), NULL);
}

void CompositeWidget::update()
{
}

void CompositeWidget::add_child(Widget * widget)
{
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
    
    if (w && h)
    {
        _bounding_rect.w = w;
        _bounding_rect.h = h;
    }
    else
    {
        SDL_Rect tmp = {x, y, 0, 0};
        for (std::vector< Widget * >::const_iterator it = _widgets.begin();
             it != _widgets.end(); ++it)
        {
            const SDL_Rect * child = (*it) -> get_bounds();
            std::cout << child -> x << ' ' << child -> y << ' ' << child -> w
                      << ' ' << child -> h << std::endl;
            SDL_UnionRect(&tmp, child, &tmp);
        }
        _bounding_rect.w = tmp.w;
        _bounding_rect.h = tmp.h;
    }

    std::cout << _bounding_rect.x << ' ' << _bounding_rect.y << ' '
              << _bounding_rect.w << ' ' << _bounding_rect.h << std::endl;
    
    TextureManager::get_instance() -> load(bg_texture_file, id, renderer); 
}

DialogBox::~DialogBox()
{}

const SDL_Rect * DialogBox::get_bounds() const
{
    return &_bounding_rect;
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
}

void DecoratorWidget::add_child(Widget * widget)
{
    _widget = widget;
}

void DecoratorWidget::remove_child(Widget * widget)
{
    _widget = NULL;
}
