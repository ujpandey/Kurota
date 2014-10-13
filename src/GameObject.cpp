#include "GameObject.h"


Player::Player(const std::string & id,
               const std::string & texture_file,
               SDL_Renderer * renderer,
               int x, int y, int w, int h)
    : _id(id), _x(x), _y(y), _w(w), _h(h)
{
    TextureManager * tm = TextureManager::get_instance();
    tm -> load(texture_file, id, renderer);
    std::cout << _id << std::endl;
}


void Player::draw(SDL_Renderer * renderer) const
{
    TextureManager * tm = TextureManager::get_instance();
    tm -> render(_id, _x, _y, _w, _h, _x, _y, _w, _h, renderer);
}

void Player::update()
{
    _x += 5;
    _y += 5;
}

std::string Player::serialize() const
{
    std::ostringstream ret_stream;
    ret_stream << _id << '|' << _x << '|' << _y << '#';
    return ret_stream.str();
}
