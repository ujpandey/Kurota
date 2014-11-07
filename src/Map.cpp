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
// Tile::Tile(const std::string & id,
//            const std::string & tileset_id,
//            const int & width,
//            const int & col,
//            const int & row,
//            const bool & traversable)
//     : _id(id), _tileset_id(id), _traversable(traversable)
// {
//     _bounding_rect.x = col * width;
//     _bounding_rect.y = row * width;
//     _bounding_rect.w = _bounding_rect.h = width;
// }

// const SDL_Rect * Cell::get_bounds() const
// {
//     return &_bounding_rect;
// }

//-----------------------------------------------------------------------------
// Cell
//-----------------------------------------------------------------------------
Cell::Cell(const std::string & id,
           const std::string & tileset_id,
           const int & x, const int & y, const int & w, const int & h,
           const int & width,
           const int & row,
           const int & col,
           const bool & empty,
           const bool & traversable)
    : GameObject(id), _tileset_id(tileset_id),
      _empty(empty), _traversable(traversable)
{
    _bounding_rect = {x, y, w, h};
    _tile_rect.x = col * width;
    _tile_rect.y = row * width;
    _tile_rect.w = _tile_rect.h = width;
}

const SDL_Rect * Cell::get_bounds() const
{
    return &_bounding_rect;
}

void Cell::draw(SDL_Renderer * renderer)
{
    TextureManager * tm = TextureManager::get_instance();
    tm -> render(_tileset_id,
                 _tile_rect.x, _tile_rect.y, _tile_rect.w, _tile_rect.h,
                 _bounding_rect.x, _bounding_rect.y,
                 _bounding_rect.w, _bounding_rect.h,
                 Game::get_instance() -> get_renderer());
}

void Cell::update()
{
}

const bool & Cell::empty() const
{
    return _empty;
}

void Cell::set_occupant(GameObject * g_o)
{
    _occupants.push_back(g_o);
}

void release_occupant(GameObject * g_o)
{
    std::vector< GameObject * >::iterator it =
        std::find(_occupants.begin(), _occupants.end(), g_o);
    if (it != _occupants.end())
        _occupants.erase(it);
}

virtual void set_neighbor(Cell * neighbor)
{
    _neighbors.push_back(neighbor);
}

virtual const std::vector< Cell * > & get_neighbors() const
{
    return _neighbors;
}

//-----------------------------------------------------------------------------
// Cell
//-----------------------------------------------------------------------------
