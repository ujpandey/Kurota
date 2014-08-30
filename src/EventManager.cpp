#include "EventManager.h"

EventManager * EventManager::instance = NULL;

EventManager * EventManager::get_instance()
{
    if (instance)
        return instance;
    instance = new EventManager;
    return instance;
}

EventManager::EventManager()
{
    for (int i = 0; i < 3; ++i)
        _mouse_button_states[i] = false;
}

void EventManager::lease(EventHandler * e_h)
{
    event_handlers.push_back(e_h);
}

void EventManager::release(EventHandler * e_h)
{
    std::vector< EventHandler * >::iterator it =
        std::find(event_handlers.begin(), event_handlers.end(), e_h);
    if (it != event_handlers.end())
        event_handlers.erase(it);
}

void EventManager::coup(EventHandler * e_h)
{
    event_handlers.push_back(e_h);
}

void EventManager::pop()
{
    event_handlers.pop_back();
}

void EventManager::clear()
{
    event_handlers.clear();
}

void EventManager::handle_event()
{
    while (SDL_PollEvent(&_event))
    {
        switch (_event.type)
        {
            case SDL_MOUSEMOTION:
                update_mpos();
                break;
            case SDL_MOUSEBUTTONDOWN:
                update_mbstates_mdown();
                break;
            case SDL_MOUSEBUTTONUP:
                update_mbstates_mup();
                break;
            default:
                break;
        }
        for (std::vector< EventHandler * >::reverse_iterator rit =
                 event_handlers.rbegin(); rit != event_handlers.rend(); ++rit)
        {
            (*rit) -> handle_event();
        }
    }
}

const vec2d & EventManager::get_mouse_position() const
{
    return _mouse_position;
}

const bool & EventManager::get_mouse_button_state(MouseButton button) const
{
    return _mouse_button_states[button];
}

const SDL_Event & EventManager::get_event() const
{
    return _event;
}

void EventManager::update_mpos()
{
    _mouse_position.set_x(_event.motion.x);
    _mouse_position.set_y(_event.motion.y);
}

void EventManager::update_mbstates_mdown()
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

void EventManager::update_mbstates_mup()
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
