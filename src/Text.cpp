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
    SDL_SetRenderDrawColor(renderer, 123, 117, 158, 255);
    SDL_RenderFillRect(renderer, get_bounds());
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    TextureManager * tm = TextureManager::get_instance();
    tm -> render_as_is(_id, _bounding_rect.x, _bounding_rect.y, renderer);
}

void TextBox::on_mouse_button_down()
{
    SDL_Point p = {_mouse_position.get_x(), _mouse_position.get_y()};
    std::cout << "HHHHH " << p.x << ' ' << p.y << ' ' << _id
              << _bounding_rect.x << ' ' << _bounding_rect.y << ' '
              << _bounding_rect.w << ' ' << _bounding_rect.h << std::endl;
    if (SDL_PointInRect(&p, get_bounds()))
    {
        std::cout << "hmm" << std::endl;
        _focus = true;
    }
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
         if (_event -> key.keysym.sym == SDLK_BACKSPACE && _text.length() > 0)
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
        std::cout << _redraw << std::endl;
        _text += _event -> text.text;
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
        std::cout << _text << std::endl;
        TextureManager * tm = TextureManager::get_instance();
        tm -> load_text(_text, _id, Game::get_instance() -> get_renderer());
        int w, h;
        SDL_QueryTexture(tm -> get_texture(_id), NULL, NULL, &w, &h);
        if (w > _bounding_rect.w)
        {
            _text.erase(_text.end() - 1);
            tm -> load_text(_text, _id, Game::get_instance() -> get_renderer());
            _maxed = true;
        }
        else
            _maxed = false;
        _redraw = false;
//         if (h > _bounding_rect.h - 28)
//             _maxed_h = true;
    }
}

const SDL_Rect * TextBox::get_bounds() const
{
    return &_bounding_rect;
}

void TextBox::set_bounds(const int & x,
                        const int & y,
                        const int & w,
                        const int & h)
{
    _bounding_rect.x = x;
    _bounding_rect.y = y;
    _bounding_rect.w = w;
    _bounding_rect.h = h;
}
