#include "TextureManager.h"


bool TextureManager::load(const std::string & filename,
                          const std::string & id,
                          const SDL_Renderer * renderer)
{
    SDL_Surface * tmp = IMG_Load(filename.c_str());

    if (!tmp)
    {
        std::cerr << "Failure loading image: "
                  << IMG_GetError() << std::endl;

        return false;
    }

    SDL_Texture * new_texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);

    if (!new_texture)
    {
        std::cerr << "Failure loading texture: "
                  << SDL_GetError() << std::endl;

        return false;
    }

    textures[id] = new_texture;
    
    return true;
}


void TextureManager::render(const std::string & id,
                            const int & src_x,
                            const int & src_y,
                            const int & src_w,
                            const int & src_h,
                            const int & dest_x,
                            const int & dest_y,
                            const int & dest_w,
                            const int & dest_h,
                            const SDL_Renderer * renderer,
                            const SDL_RenderFlip & flip)
{
    SDL_Rect src, dest;
    src.x = src_x;
    src.y = src_y;
    src.w = src_w;
    src.h = src_h;
    dest.x = dest_x;
    dest.y = dest_y;
    dest.w = dest_w;
    dest.h = dest_h;

    SDL_RenderCopyEx(renderer, textures[id], &src, &dest, 0, 0, flip);    
}
