#include "EventHandler.h"

bool EventHandler::_mouse_button_states[3];
SDL_Event EventHandler::_event;
vec2d EventHandler::_mouse_position;

EventHandler::EventHandler()
    : _successor(NULL)
{
    for (int i = 0; i < 3; ++i)
        _mouse_button_states[i] = false;
}

EventHandler::~EventHandler()
{
}

void EventHandler::handle_event()
{
    while (SDL_PollEvent(&_event))
    {
        switch (_event.type)
        {
            case SDL_QUIT:
                Game::get_instance()->set_status(INACTIVE);
                break;
            case SDL_MOUSEMOTION:
                update_mpos();
                on_mouse_move();
                break;
            case SDL_MOUSEBUTTONDOWN:
                update_mbstates_mdown();
                on_mouse_button_down();
                break;
            case SDL_MOUSEBUTTONUP:
                update_mbstates_mup();
                on_mouse_button_up();
                break;
            case SDL_KEYDOWN:
                on_key_down();
                break;
            case SDL_KEYUP:
                on_key_up();
                break;
            case SDL_TEXTINPUT:
                on_text_input();
                break;
            default:
                break;
        }
    }
}

void EventHandler::on_mouse_move()
{
    if (_successor != NULL)
    {
        _successor -> on_mouse_move();
    }
}

void EventHandler::on_mouse_button_down()
{
    if (_successor != NULL)
    {
        _successor -> on_mouse_button_down();
    }
}

void EventHandler::on_mouse_button_up()
{
    if (_successor != NULL)
        _successor -> on_mouse_button_up();
}

void EventHandler::on_key_down()
{
    if (_successor != NULL)
        _successor -> on_key_down();
}

void EventHandler::on_key_up()
{
    if (_successor != NULL)
        _successor -> on_key_up();
}

void EventHandler::on_text_input()
{
    if (_successor != NULL)
        _successor -> on_text_input();
}

const vec2d & EventHandler::get_mouse_position() const
{
    return _mouse_position;
}

bool EventHandler::get_mouse_button_state(MouseButton button) const
{
    return _mouse_button_states[button];
}

void EventHandler::set_successor(EventHandler * successor)
{
    _successor = successor;
}

void EventHandler::update_mpos()
{
    _mouse_position.set_x(_event.motion.x);
    _mouse_position.set_y(_event.motion.y);
}

void EventHandler::update_mbstates_mdown()
{
    if (_event.button.button == SDL_BUTTON_LEFT)
    {
        _mouse_button_states[LEFT] = true;
    }
    else if (_event.button.button == SDL_BUTTON_MIDDLE)
    {
        _mouse_button_states[MIDDLE] = true;
    }
    else if (_event.button.button == SDL_BUTTON_RIGHT)
    {
        _mouse_button_states[RIGHT] = true;
    }
}

void EventHandler::update_mbstates_mup()
{
    if (_event.button.button == SDL_BUTTON_LEFT)
    {
        _mouse_button_states[LEFT] = false;
    }
    else if (_event.button.button == SDL_BUTTON_MIDDLE)
    {
        _mouse_button_states[MIDDLE] = false;
    }
    else if (_event.button.button == SDL_BUTTON_RIGHT)
    {
        _mouse_button_states[RIGHT] = false;
    }
}
