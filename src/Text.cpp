#include "Text.h"
#include "TextureManager.h"
#include "EventManager.h"

//-----------------------------------------------------------------------------
// TextBox
//-----------------------------------------------------------------------------
TextBox::TextBox(const std::string & id,
                 const std::string & text,
                 int x, int y, int w, int h, bool password)
    : Widget(id), _text(text), _focus(false), _redraw(false), _maxed(false),
      _password(password)
{
    _bgcolor.r = 179;
    _bgcolor.g = 193;
    _bgcolor.b = 158;
    _bgcolor.a = 255;
    _textcolor.r = 54;
    _textcolor.g = 69;
    _textcolor.b = 79;
    _textcolor.a = 255;
    _bounding_rect.x = x;
    _bounding_rect.y = y;
    _bounding_rect.w = w;
    _bounding_rect.h = h;
    if (_password)
    {
        std::string pwtext = _text;
        pwtext.replace(pwtext.begin(), pwtext.end(), pwtext.size(), 178);
        TextureManager::get_instance() ->
            load_text(pwtext, _id, _textcolor, Game::get_instance() -> get_renderer());
    }
    else
        TextureManager::get_instance() ->
            load_text(_text, _id, _textcolor, Game::get_instance() -> get_renderer());
}

TextBox::~TextBox()
{
}

void TextBox::draw(SDL_Renderer * renderer) const
{
    Uint8 r, g, b, a;
    SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    SDL_SetRenderDrawColor(renderer, _bgcolor.r, _bgcolor.g, _bgcolor.b, _bgcolor.a);
    SDL_RenderFillRect(renderer, get_bounds());
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    TextureManager * tm = TextureManager::get_instance();
    tm -> render_as_is(_id, _bounding_rect.x, _bounding_rect.y, renderer);
    if (_focus)
    {
        int x = _bounding_rect.x;
        int y = _bounding_rect.y;
        int w, h;
        SDL_QueryTexture(tm -> get_texture(_id), NULL, NULL, &w, &h);
        SDL_Rect highlight = {x - 1, y - 1,
                              _bounding_rect.w + 2, _bounding_rect.h + 2};
        SDL_SetRenderDrawColor(renderer, 152, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &highlight);
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
        if (_text.empty())
            w = 3;
        SDL_Rect cursor = {x + w + 2, y + 2, 1, 26};
        SDL_RenderFillRect(renderer, &cursor);
    }
}

void TextBox::on_mouse_button_down()
{
    vec2d _mouse_position = EventManager::get_instance() -> get_mouse_position();
    SDL_Point p = {_mouse_position.get_x(), _mouse_position.get_y()};
    if (SDL_PointInRect(&p, get_bounds()))
    {
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
    SDL_Event _event = EventManager::get_instance() -> get_event();
    if (_focus)
    {
         if (_event.key.keysym.sym == SDLK_BACKSPACE && _text.length() > 0)
         {
             _text.erase(_text.end() - 1);
             _redraw = true;
         }
         else
             _successor -> on_key_down();
    }
    else
    {
        _successor -> on_key_down();
    }
}

void TextBox::on_text_input()
{
    SDL_Event _event = EventManager::get_instance() -> get_event();
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
        if (_password)
        {
            std::string pwtext = _text.replace(_text.begin(), _text.end(), _text.size(), '*');
            tm -> load_text(pwtext, _id, _textcolor, Game::get_instance() -> get_renderer());
        }
        else
            tm -> load_text(_text, _id, _textcolor, Game::get_instance() -> get_renderer());
        int w, h;
        SDL_QueryTexture(tm -> get_texture(_id), NULL, NULL, &w, &h);
        if (w > _bounding_rect.w)
        {
            _text.erase(_text.end() - 1);
            if (_password)
            {
                std::string pwtext = _text.replace(_text.begin(), _text.end(), _text.size(), '*');
                tm -> load_text(pwtext, _id, _textcolor, Game::get_instance() -> get_renderer());
            }
            else
                tm -> load_text(_text, _id, _textcolor, Game::get_instance() -> get_renderer());
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

void TextBox::set_focus()
{
    _focus = true;
}

const std::string & TextBox::get_text() const
{
    return _text;
}

//-----------------------------------------------------------------------------
// TextArea
//-----------------------------------------------------------------------------
TextArea::TextArea(const std::string & id,
                 const std::string & text,
                 int x, int y, int w, int h)
    : Widget(id), _text(text), _redraw(false)
{
    _bounding_rect.x = x;
    _bounding_rect.y = y;
    _bounding_rect.w = w;
    _bounding_rect.h = h;
    _textcolor.r = 152;
    _textcolor.g = 155;
    _textcolor.b = 255;
    _textcolor.a = 255;
    TextureManager::get_instance()
        -> load_text(_text, _id, _textcolor, Game::get_instance() -> get_renderer());
    // Assume responsibility to fit text in the area is on client for now.
    // int w, h;
//     SDL_QueryTexture(tm -> get_texture(_id), NULL, NULL, &w, &h);     
}

TextArea::~TextArea()
{
}

void TextArea::draw(SDL_Renderer * renderer) const
{
    TextureManager * tm = TextureManager::get_instance();
    tm -> render_as_is(_id, _bounding_rect.x, _bounding_rect.y, renderer);
}

void TextArea::update()
{
    if (_redraw)
    {
        TextureManager * tm = TextureManager::get_instance();
        tm -> load_text(_text, _id, _textcolor, Game::get_instance() -> get_renderer());
        int w, h;
        SDL_QueryTexture(tm -> get_texture(_id), NULL, NULL, &w, &h);
        if (w > _bounding_rect.w)
        {
            _text.erase(_text.end() - 1);
            tm -> load_text(_text, _id, _textcolor, Game::get_instance() -> get_renderer());
        }
        _redraw = false;
    }
}

const SDL_Rect * TextArea::get_bounds() const
{
    return &_bounding_rect;
}

void TextArea::set_bounds(const int & x,
                        const int & y,
                        const int & w,
                        const int & h)
{
    _bounding_rect.x = x;
    _bounding_rect.y = y;
    _bounding_rect.w = w;
    _bounding_rect.h = h;
}

void TextArea::set_text(const std::string & text)
{
    _text = text;
    _redraw = true;
}
