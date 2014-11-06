#ifndef MAP_H
#define MAP_H

#include "GameObject.h"

enum TileType { GRASS, GROUND, PAVEMENT, VEGETATION, WATER };

Class TileSet
{
public:
    TileSet(const std::string & id, const std::string & filename);
    ~TileSet();
    const std::string & get_id() const;
    
private:
    std::string _id;
};

Class Tile : public GameObject
{
public:
    Tile(const std::string & id, int num, int size,
         int x, int y, int w, int h);
    virtual const SDL_Rect * get_bounds() const;
    virtual void draw();
    virtual void update();

    virtual const bool & empty() const;
    virtual void release_occupant(GameObject * g_o);
    virtual void set_occupant(GameObject * g_o);
    
protected:
    bool _empty;
    SDL_Rect _bounding_rect;
    std::vector< Tile * > neighbors;
    std::vector< GameObject * > occupants;
};

Class Map : public GameObject
{
public:
    Map();
    virtual ~Map();

private:
    std::vector< Cell * > cells;
};

#endif
