#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <map>
#include "SDL.h"

class TextureManager
{
public:
    bool load(const std::string & filename,
              const std::string & id,
              const SDL_Renderer * renderer);
    void render(const std::string & id,
                const int & src_x,
                const int & src_y,
                const int & src_w,
                const int & src_h,
                const int & dest_x,
                const int & dest_y,
                const int & dest_w,
                const int & dest_h,
                const SDL_Renderer * renderer,
                const SDL_RenderFlip & flip);
    
private:
    std::map< std::string, SDL_Texture * > textures;
};

#endif
