#include "EventHandler.h"


EventHandler * EventHandler::instance = NULL;


EventHandler * EventHandler::get_instance()
{
    if (instance)
        return instance;
    instance = new EventHandler;
    return instance;
}


void EventHandler::update()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                TheGame::Instance()->set_status(INACTIVE);
                break;
            case SDL_MOUSEMOTION:
                on_mouse_move(event);
                break;
            case SDL_MOUSEBUTTONDOWN:
                on_mouse_button_down(event);
                break;
            case SDL_MOUSEBUTTONUP:
                on_mouse_button_up(event);
                break;
            case SDL_KEYDOWN:
                on_key_down();
                break;
            case SDL_KEYUP:
                on_key_up();
                break;
            default:
                break;
        }
    }
}
