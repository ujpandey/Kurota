#include "Widget.h"

//-----------------------------------------------------------------------------
// Widget
//-----------------------------------------------------------------------------
Widget::Widget(const std::string & id)
    : _id(id)
{}

void Widget::draw(SDL_Renderer * renderer)
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

void CompositeWidget::draw(SDL_Renderer * renderer)
{
    for (std::vector< Widget * >::iterator it = _widgets.begin();
         it != _widgets.end(); ++it)
    {
        (*it) -> draw(renderer);
    }
    
    SDL_RenderDrawRect(renderer, get_bounds());
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
// DecoratorWidget
//-----------------------------------------------------------------------------
DecoratorWidget::DecoratorWidget(const std::string & id)
    : Widget(id)
{}

DecoratorWidget::~DecoratorWidget()
{
    delete _widget;
}

void DecoratorWidget::draw(SDL_Renderer * renderer)
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
