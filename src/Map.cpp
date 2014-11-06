#include "Map.h"
#include "Game.h"
#include "TextureManager.h"

//-----------------------------------------------------------------------------
// TileSet
//-----------------------------------------------------------------------------
TileSet::TileSet(const std::string & id, const std::string & filename)
    : _id(id)
{
    TextureManager * tm = TextureManager::get_instance();
    tm -> load(filename, _id, Game::get_instance() -> get_renderer());
}

TileSet::~TileSet()
{
    TextureManger * tm = TextureManager::get_instance();
    tm -> erase(_id);
}

const std::string & TileSet::get_id()
{
    return _id;
}

//-----------------------------------------------------------------------------
// Tile
//-----------------------------------------------------------------------------
Tile::Tile(const std::string & id,
           int x, int y, int w, int h)
    : GameObject(id)
{
    _bounding_rect = {x, y, w, h};
}

const SDL_Rect * Tile::get_bounds() const
{
    retrun &_bounding_rect;
}

void Tile::draw()
{
}
