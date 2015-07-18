#include "EventHandler.h"
#include "EventManager.h"

EventHandler::EventHandler(const std::string & id)
    : _id(id), _successor(NULL)
{
}

EventHandler::~EventHandler()
{
}

void EventHandler::handle_event()
{
    SDL_Event _event = EventManager::get_instance() -> get_event();
    //std::cout << "Handling event for " << _id << std::endl;
    switch (_event.type)
    {
        case SDL_QUIT:
            on_quit();
            break;
        case SDL_MOUSEMOTION:
            on_mouse_move();
            break;
        case SDL_MOUSEBUTTONDOWN:
            on_mouse_button_down();
            break;
        case SDL_MOUSEBUTTONUP:
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

void EventHandler::set_successor(EventHandler * successor)
{
    _successor = successor;
}

const std::string & EventHandler::get_id() const
{
    return _id;
}
