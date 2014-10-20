#include "TextureManager.h"


TextureManager * TextureManager::instance = NULL;


TextureManager * TextureManager::get_instance()
{
    if (instance)
        return instance;
    instance = new TextureManager;
    return instance;
}


bool TextureManager::load(const std::string & filename,
                          const std::string & id,
                          SDL_Renderer * renderer)
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


bool TextureManager::load_text(const std::string & text,
                               const std::string & id,
                               SDL_Renderer * renderer)
{
    TTF_Font * f = Game::get_instance() -> get_font();
    SDL_Color color = {152, 255, 255, 0};
    if (text.length() > 0)
    {
        SDL_Surface * tmp = TTF_RenderText_Solid(f, text.c_str(), color);
        if (!tmp)
        {
            std::cerr << "Failure loading text: "
                      << TTF_GetError() << std::endl;
            
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
    textures[id] = NULL;
    
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
                            SDL_Renderer * renderer,
                            const SDL_RendererFlip & flip)
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

void TextureManager::erase(const std::string & id)
{
    SDL_DestroyTexture(textures[id]);
    textures.erase(id);
}

void TextureManager::clear()
{
    for (std::map< std::string, SDL_Texture * >::iterator it = textures.begin();
         it != textures.end(); ++it)
    {
        SDL_DestroyTexture(it -> second);
    }
    textures.clear();
}
