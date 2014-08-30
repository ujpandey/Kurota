#include "GameObject.h"
#include "Game.h"
#include "TextureManager.h"
#include "EventManager.h"

Player::Player(const std::string & id,
               const std::string & texture_file,
               SDL_Renderer * renderer,
               int x, int y, int w, int h)
    : GameObject(id), _position(x, y), _w(w), _h(h), _hp(100), _mana(100),
      _velocity(0, 0), _acceleration(0, 0), _target_position(0, 0),
      _moving(false)
{
    TextureManager::get_instance() -> load(texture_file, id, renderer);
    _timer.start();
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
//         double time_elapsed = _timer.get_ticks() / 1000;
//         _timer.reset();
        vec2d diff =_target_position - _position;
        _velocity = diff / diff.len() * 10;
        //std::cout << _velocity << std::endl;

//         int xsign = diff.get_x() > 0 ? 1 : -1;
//         int ysign = diff.get_y() > 0 ? 1 : -1;
        
//         bool x_close_enough = abs(diff.get_x()) < 5.0;
//         bool y_close_enough = abs(diff.get_y()) < 5.0;
//         if (!x_close_enough)
//         {
//             _velocity.set_x(xsign * 10);
//         }
//         else if (!y_close_enough)
//         {
//             _velocity.set_x(0);
//             _velocity.set_y(ysign * 10);
//         }
        if (_position.almost_equals(_target_position))
        {
            _velocity = vec2d(0, 0);
            _target_position = vec2d(0, 0);
            _moving = false;
        }
        _position += _velocity;
        //_position += _velocity * time_elapsed;
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

void Player::respawn()
{
    _hp = 100;
    _mana = 100;
}

std::string Player::serialize() const
{
    std::ostringstream ret_stream;
    ret_stream << _id << ' ' << _hp << ' ' << _mana << ' '
               << _position.get_x() << ' ' << _position.get_y()
               << _target_position.get_x() << ' ' << _target_position.get_y() << ' '
               << _velocity.get_x() << ' ' << _velocity.get_y() << ' '
               << _facing << ' ';
    return ret_stream.str();
}

void Player::deserialize(const std::string & serialized)
{
    std::istringstream in_stream(serialized);
    int facing;
    double px, py, tx, ty, vx, vy;
    in_stream >> _id >> _hp >> _mana >> px >> py >> tx >> ty >> vx >> vy >> facing;
    _position.set_x(px);
    _position.set_y(py);
    _target_position.set_x(tx);
    _target_position.set_y(ty);
    _velocity.set_x(vx);
    _velocity.set_y(vy);
    _facing = static_cast< Direction >(facing);
}


RemotePlayer::RemotePlayer(const std::string & id,
               const std::string & texture_file,
               SDL_Renderer * renderer,
               int x, int y, int w, int h)
    : Player(id, texture_file, renderer, x, y, w, h)
{
    TextureManager::get_instance() -> load(texture_file, id, renderer);
    _timer.start();
}

void RemotePlayer::on_mouse_button_down()
{
    _successor -> on_mouse_button_down();
}

std::string RemotePlayer::serialize() const
{
    std::cerr << "Shouldn't serialize remote content." << std::endl;
    exit(-1);
    return "NOPE";
}

void RemotePlayer::on_ntwk_update(const std::string & netstr)
{
    deserialize(netstr);
    _moving = true;
}
