#include "GameObject.h"


Player::Player(const std::string & id,
               const std::string & texture_file,
               SDL_Renderer * renderer,
               int x, int y, int w, int h)
    : id(id), x(x), y(y), w(w), h(h)
{
    TextureManager * tm = TextureManager::get_instance();
    tm -> load(texture_file, id, renderer);
    std::cout << this -> id << std::endl;
}


void Player::draw(SDL_Renderer * renderer)
{
    TextureManager * tm = TextureManager::get_instance();
    tm -> render(id, x, y, w, h, x, y, w, h, renderer);
}

void Player::update()
{
    x += 5;
    y += 5;
}
