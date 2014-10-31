#ifndef INCLUDES_H
#define INCLUDES_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include <deque>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "Vec2.h"

SDL_FORCE_INLINE SDL_bool SDL_PointInRect(const SDL_Point *p, const SDL_Rect *r)
{
    return ( (p->x >= r->x) && (p->x < (r->x + r->w)) &&
             (p->y >= r->y) && (p->y < (r->y + r->h)) ) ? SDL_TRUE : SDL_FALSE;
}

#endif
