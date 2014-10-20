#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include "Game.h"

class TextureManager
{
public:
    static TextureManager * get_instance();
    bool load(const std::string & filename,
              const std::string & id,
              SDL_Renderer * renderer);
    bool load_text(const std::string & text,
                   const std::string & id,
                   SDL_Renderer * renderer);
    void render(const std::string & id,
                const int & src_x,
                const int & src_y,
                const int & src_w,
                const int & src_h,
                const int & dest_x,
                const int & dest_y,
                const int & dest_w,
                const int & dest_h,
                SDL_Renderer * renderer,
                const SDL_RendererFlip & flip=SDL_FLIP_NONE);
    void erase(const std::string &id);
    void clear();

protected:
    TextureManager(){}

private:
    static TextureManager * instance;
    std::map< std::string, SDL_Texture * > textures;
};

#endif
