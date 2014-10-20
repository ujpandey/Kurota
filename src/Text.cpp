#include "Text.h"

TextBox::TextBox(const std::string & id,
                 const std::string & text,
                 int x, int y, int w, int h)
    : Widget(id), _text(text), _focus(false), _redraw(false), _maxed(false)
{
    _bounding_rect.x = x;
    _bounding_rect.y = y;
    _bounding_rect.w = w;
    _bounding_rect.h = h;
    TextureManager::get_instance()
        -> load_text(_text, _id, Game::get_instance() -> get_renderer());
}

TextBox::~TextBox()
{
}

void TextBox::draw(SDL_Renderer * renderer) const
{
    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, get_bounds());
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    TextureManager * tm = TextureManager::get_instance();
    tm -> render_as_is(_id, _bounding_rect.x, _bounding_rect.y, renderer);
}

void TextBox::on_mouse_button_down()
{
    SDL_Point p = {_mouse_position.get_x(), _mouse_position.get_y()};
    if (SDL_PointInRect(&p, get_bounds()))
        _focus = true;
    else
    {
        _focus = false;
        _successor -> on_mouse_button_down();
    }
}

void TextBox::on_key_down()
{
    if (_focus)
    {
         if (_event.key.keysym.sym == SDLK_BACKSPACE && _text.length() > 0)
         {
             _text.erase(_text.end() - 1);
             _redraw = true;
         }
    }
    else
    {
        _successor -> on_key_down();
    }
}

void TextBox::on_text_input()
{
    if (_focus && !_maxed)
    {
        _text += _event.text.text;
        _redraw = true;
    }
    else
    {
        _successor -> on_text_input();
    }
}

void TextBox::update()
{
    if (_redraw)
    {
        TextureManager * tm = TextureManager::get_instance();
        tm -> load_text(_text, _id, Game::get_instance() -> get_renderer());
        int w, h;
        SDL_QueryTexture(tm -> get_texture(_id), NULL, NULL, &w, &h);
        if (w > _bounding_rect.w - 28)
            _maxed = true;
        else
            _maxed = false;
//         if (h > _bounding_rect.h - 28)
//             _maxed_h = true;
    }
}

const SDL_Rect * TextBox::get_bounds() const
{
    return &_bounding_rect;
}
