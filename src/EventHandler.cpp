#include "EventHandler.h"

bool EventHandler::_mouse_button_states[3];
SDL_Event * EventHandler::_event;
vec2d EventHandler::_mouse_position;

EventHandler::EventHandler(const std::string & id)
    : _id(id), _successor(NULL)
{
    for (int i = 0; i < 3; ++i)
        _mouse_button_states[i] = false;
}

EventHandler::~EventHandler()
{
}

void EventHandler::register_event(SDL_Event * event)
{
    _event = event;
}

void EventHandler::handle_event()
{
    //std::cout << "Handling event for " << _id << std::endl;
    switch (_event -> type)
    {
        case SDL_QUIT:
            on_quit();
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

void EventHandler::on_quit()
{
    //std::cout << "Handling quit for " << _id << std::endl;
    if (_successor)
        _successor -> on_quit();
}

void EventHandler::on_mouse_move()
{
    //std::cout << "Handling mmove for " << _id << std::endl;
    if (_successor != NULL)
    {
        _successor -> on_mouse_move();
    }
}

void EventHandler::on_mouse_button_down()
{
    //std::cout << "Handling mb down for " << _id << std::endl;
    if (_successor != NULL)
    {
        _successor -> on_mouse_button_down();
    }
}

void EventHandler::on_mouse_button_up()
{
    //std::cout << "Handling mb up for " << _id << std::endl;
    if (_successor != NULL)
        _successor -> on_mouse_button_up();
}

void EventHandler::on_key_down()
{
    //std::cout << "Handling key down for " << _id << std::endl;
    if (_successor != NULL)
        _successor -> on_key_down();
}

void EventHandler::on_key_up()
{
    //std::cout << "Handling key up for " << _id << std::endl;
    if (_successor != NULL)
        _successor -> on_key_up();
}

void EventHandler::on_text_input()
{
    // std::cout << "Handling text input for " << _id << std::endl;
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
    _mouse_position.set_x(_event -> motion.x);
    _mouse_position.set_y(_event -> motion.y);
}

void EventHandler::update_mbstates_mdown()
{
    if (_event -> button.button == SDL_BUTTON_LEFT)
    {
        _mouse_button_states[LEFT] = true;
    }
    else if (_event -> button.button == SDL_BUTTON_MIDDLE)
    {
        _mouse_button_states[MIDDLE] = true;
    }
    else if (_event -> button.button == SDL_BUTTON_RIGHT)
    {
        _mouse_button_states[RIGHT] = true;
    }
}

void EventHandler::update_mbstates_mup()
{
    if (_event -> button.button == SDL_BUTTON_LEFT)
    {
        _mouse_button_states[LEFT] = false;
    }
    else if (_event -> button.button == SDL_BUTTON_MIDDLE)
    {
        _mouse_button_states[MIDDLE] = false;
    }
    else if (_event -> button.button == SDL_BUTTON_RIGHT)
    {
        _mouse_button_states[RIGHT] = false;
    }
}

const std::string & EventHandler::get_id() const
{
    return _id;
}
