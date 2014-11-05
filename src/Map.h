#ifndef MAP_H
#define MAP_H

#include "GameObject.h"

Class Tile : public GameObject
{
public:
    Tile(const std::string & id,
}

Class Cell : public GameObject
{
public:
    Cell(const int & x, const int & y, );
    virtual ~Cell();


private:
    std::vector< Cell * > neighbors;
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
