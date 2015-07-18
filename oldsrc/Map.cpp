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
           const int & col,
           const int & row,
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

void Cell::release_occupant(GameObject * g_o)
{
    std::vector< GameObject * >::iterator it =
        std::find(_occupants.begin(), _occupants.end(), g_o);
    if (it != _occupants.end())
        _occupants.erase(it);
}

const std::vector< GameObject * > & Cell::get_occupants() const
{
    return _occupants;
}

void Cell::set_neighbor(Cell * neighbor)
{
    _neighbors.push_back(neighbor);
}

void Cell::release_neighbor(Cell * neighbor)
{
    std::vector< Cell * >::iterator it =
        std::find(_neighbors.begin(), _neighbors.end(), neighbor);
    if (it != _neighbors.end())
        _neighbors.erase(it);
}

const std::vector< Cell * > & Cell::get_neighbors() const
{
    return _neighbors;
}

//-----------------------------------------------------------------------------
// Map
//-----------------------------------------------------------------------------
Map::Map(const std::string & id,
         const std::string & tileset_id,
         const int & width=640
         const int & num_rows=10,
         const int & num_cols=10)
    : _id(id), _tileset_id(tileset_id), _width(width)
      _num_rows(num_rows), _num_cols(num_cols),
      _cell_width(_width / _num_rows)
{
    generate();
}

Map::~Map()
{
    for (std::vector< std::vector< Cell * > * >::iterator it = _rows.begin();
         it != _rows.end(); ++it)
    {
        for (std::vector< Cell * >::iterator jk = it -> begin();
             jk ! = it -> end(); ++jk)
        {
            delete (*jk); 
        }
    }
}
