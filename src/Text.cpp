#include "Text.h"

TextBox::TextBox(const std::string & id,
                 const std::string & text,
                 int x, int y, int w, int h)
    : Widget(id), _text(text), _focus(false), _redraw(false)
{
    _bounding_rect.x = x;
    _bounding_rect.y = y;
    _bounding_rect.w = w;
    _bounding_rect.h = h;
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
    if (_text.length() > 0)
        tm -> render(_id, 0, 0, _bounding_rect.w, _bounding_rect.h,
                     _bounding_rect.x, _bounding_rect.y,
                     _bounding_rect.w, _bounding_rect.h, renderer);
}

void TextBox::update()
{
    EventHandler * eh = EventHandler::get_instance();

    if (_focus)
    {
        SDL_StartTextInput();
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            std::cout << "hallelujah" << "T_T" << std::endl;
            if (e.type == SDL_KEYDOWN)
            {
                std::cout << "hallelujah ..." << std::endl;
                if (e.key.keysym.sym == SDLK_BACKSPACE && _text.length() > 0)
                {
                    _text.erase(_text.end() - 1);
                    _redraw = true;
                }
            }
            else if (e.type == SDL_TEXTINPUT)
            {
                std::cout << "hallelujah" << std::endl;
                _text += e.text.text;
                _redraw = true;
            }
        }
        SDL_StopTextInput();

        vec2d mpos = eh -> get_mouse_position();
        SDL_Point mpoint = {mpos.get_x(), mpos.get_y()};
        if (eh -> get_mouse_button_state(LEFT)
            && !SDL_PointInRect(&mpoint, get_bounds()))
            _focus = false;
        

        if (_redraw)
        {
            TextureManager::get_instance() -> load_text(
                _text, _id, Game::get_instance() -> get_renderer());
            _redraw = false;
        }
    }
    else
    {
        vec2d mpos = eh -> get_mouse_position();
        SDL_Point mpoint = {mpos.get_x(), mpos.get_y()};
        if (eh -> get_mouse_button_state(LEFT)
            && SDL_PointInRect(&mpoint, get_bounds()))
            _focus = true;
    }
}

const SDL_Rect * TextBox::get_bounds() const
{
    return &_bounding_rect;
}
