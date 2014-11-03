#include "GameObject.h"
#include "Game.h"
#include "TextureManager.h"
#include "EventManager.h"

Player::Player(const std::string & id,
               const std::string & texture_file,
               SDL_Renderer * renderer,
               int x, int y, int w, int h)
    : GameObject(id), _position(x, y), _w(w), _h(h),
      _velocity(0, 0), _acceleration(0, 0), _target_position(0, 0),
      _moving(false)
{
    TextureManager::get_instance() -> load(texture_file, id, renderer);
}

void Player::draw(SDL_Renderer * renderer) const
{
    TextureManager::get_instance() ->
        render(_id, 0, 0, _w, _h, _position.get_x(), _position.get_y(), _w, _h, renderer);
}

void Player::update()
{
    //_velocity += _acceleration;
    //std::cout << _moving << std::endl;
    if (_moving)
    {
        vec2d diff =_target_position - _position; 
        _velocity = diff / diff.len() * 10;
        //std::cout << _velocity << std::endl;
        /*
          bool x_close_enough = abs(_target_position.get_x() - _position.get_x()) < 2.0;
        bool y_close_enough = abs(_target_position.get_y() - _position.get_y()) < 2.0;
        if (!x_close_enough)
        {
            if (_target_position.get_x() < _position.get_x())
                _velocity.set_x(-1 * 10);
            else //if (_target_position.get_x() > _position.get_x())
                _velocity.set_x(1 * 10);
            _moving = true;
        }
        else if (!y_close_enough)
        {
            std::cout << "fuck" << std::endl;
            _velocity.set_x(0);
            if (_target_position.get_y() < _position.get_y())
                _velocity.set_y(-1 * 10);
            else //if (_target_position.get_y() > _position.get_y())
                _velocity.set_y(1 * 10);
            _moving = true;
        }
        else
        {
            _velocity = vec2d(0, 0);
            _target_position = vec2d(0, 0);
            _moving = false;
        }
        */
        if (_position.almost_equals(_target_position))
        {
            _velocity = vec2d(0, 0);
            _target_position = vec2d(0, 0);
            _moving = false;
        }
        _position += _velocity;
    }
}

void Player::on_mouse_button_down()
{
    vec2d _mouse_position = EventManager::get_instance() -> get_mouse_position();
    SDL_Point p = {_mouse_position.get_x(), _mouse_position.get_y()};
    if (SDL_PointInRect(&p, Game::get_instance() -> get_map_bounds()))
    {
        _target_position = _mouse_position;
        _moving = true;
    }
    else
        _successor -> on_mouse_button_down();
}

std::string Player::serialize() const
{
    std::ostringstream ret_stream;
    ret_stream << _id << '|' << _position.get_x() << '|' << _position.get_y() << '#';
    return ret_stream.str();
}
