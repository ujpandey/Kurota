#include "EventHandler.h"


EventHandler * EventHandler::instance = NULL;


EventHandler * EventHandler::get_instance()
{
    if (instance)
        return instance;
    instance = new EventHandler;
    return instance;
}

EventHandler::EventHandler()
{
    for (int i = 0; i < 3; ++i)
        mouse_button_states[i] = false;
}

void EventHandler::update()
{
    SDL_Event event;
    key_states = SDL_GetKeyboardState(NULL);
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                Game::get_instance()->set_status(INACTIVE);
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

void EventHandler::on_mouse_move(SDL_Event & event)
{
    mouse_position.set_x(event.motion.x);
    mouse_position.set_y(event.motion.y);
}

void EventHandler::on_mouse_button_down(SDL_Event & event)
{
    if(event.button.button == SDL_BUTTON_LEFT)
    {
        mouse_button_states[LEFT] = true;
    }
    else if(event.button.button == SDL_BUTTON_MIDDLE)
    {
        mouse_button_states[MIDDLE] = true;
    }
    else if(event.button.button == SDL_BUTTON_RIGHT)
    {
        mouse_button_states[RIGHT] = true;
    }
}

void EventHandler::on_mouse_button_up(SDL_Event & event)
{
    if(event.button.button == SDL_BUTTON_LEFT)
    {
        mouse_button_states[LEFT] = false;
    }
    else if(event.button.button == SDL_BUTTON_MIDDLE)
    {
        mouse_button_states[MIDDLE] = false;
    }
    else if(event.button.button == SDL_BUTTON_RIGHT)
    {
        mouse_button_states[RIGHT] = false;
    }
}

void EventHandler::on_key_down()
{
}

void EventHandler::on_key_up()
{
}

const vec2d & EventHandler::get_mouse_position() const
{
    return mouse_position;
}

bool EventHandler::get_mouse_button_state(MouseButton button) const
{
    return mouse_button_states[button];
}

bool EventHandler::is_key_down(SDL_Scancode key)
{
    if (key_states == NULL)
        return false;
    if (key_states[key])
        return true;
    return false;
}

