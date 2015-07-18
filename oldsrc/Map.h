#ifndef MAP_H
#define MAP_H

#include "GameObject.h"

class TileSet
{
public:
    TileSet(const std::string & id, const std::string & filename);
    ~TileSet();
    const std::string & get_id() const;
    
private:
    std::string _id;
};

// class Tile
// {
// public:
//     Tile(const std::string & id,
//          const std::string & tileset_id,
//          const int & width=64,
//          const int & row=0,
//          const int & col=0,
//          const bool & traversable=true);
//     virtual ~Tile();
    
//     virtual const SDL_Rect * get_bounds() const;
//     const std::string & get_id() const;


//     std::string _id;
//     std::string _tileset_id;
//     bool _traversable;
//     SDL_Rect _bounding_rect;
// };

class Cell : public GameObject
{
public:
    Cell(const std::string & id,
         const std::string & tileset_id,
         const int & x=0, const int & y=0,
         const int & w=64, const int & h=64,
         const int & width=64,
         const int & col=0,
         const int & row=0,
         const bool & empty=true,
         const bool & traversable=true);
    virtual ~Cell();
    
    virtual const SDL_Rect * get_bounds() const;
    virtual void draw(SDL_Renderer * renderer) const;
    virtual void update();

    virtual const bool & empty() const;

    virtual void set_occupant(GameObject * g_o);
    virtual void release_occupant(GameObject * g_o);
    virtual const std::vector< GameObject * > & get_occupants() const;
    
    virtual void set_neighbor(Cell * neighbor);
    virtual void release_neighbor(Cell * neighbor);
    virtual const std::vector< Cell * > & get_neighbors() const;

protected:
    std::string _tileset_id;
    bool _empty;
    bool _traversable;
    SDL_Rect _bounding_rect;
    SDL_Rect _tile_rect;
    std::vector< Cell * > _neighbors;
    std::vector< GameObject * > _occupants;
};

class Map : public GameObject
{
public:
    Map(const std::string & id,
        const std::string & tileset_id,
        const int & width=640,
        const int & num_cols=10,
        const int & num_rows=10
        );
    virtual ~Map();
    
    void load(const std::string & filename="kurota.map");
    void save(const std::string & filename="kurota.map");

    virtual void draw(SDL_Renderer * renderer) const;
    virtual void update();

    virtual void generate();

    std::string _id;
    std::string _tileset_id;
    int _width, _num_cols, _num_rows, _cell_width;
    std::vector< std::vector< Cell * > * > _rows;
};

#endif
