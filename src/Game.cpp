// File: Game.cpp
// Author: Ujjwal Jung Pandey
// Description: Implementation of game controller.


#include <iostream>


#include "Game.h"


bool Game::init(const int & lib_flags,
                const std::string & title,
                const int & win_x,
                const int & win_y,
                const int & win_w,
                const int & win_h,
                const int & win_flags,
                const int & clear_color_r,
                const int & clear_color_g,
                const int & clear_color_b,
                const int & clear_color_a)
{
    if (SDL_Init(lib_flags) != 0)
    {
        std::cerr << "SDL initiation failed: " << SDL_GetError() << std::endl;

        return false;
    }

    window = SDL_CreateWindow(title.c_str(), win_x, win_y, win_w, win_h, win_flags);
    if (window == NULL)
    {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;

        return false;
    }

    // SDL_image initiation
    int IMG_flags = IMG_INIT_PNG | IMG_INIT_JPG;
    int IMG_init_code = IMG_Init(IMG_flags);

    if (IMG_init_code & IMG_flags != IMG_flags)
    {
        std::cerr << "SDL_image initiation failed: "
                  << IMG_GetError() << std::endl;

        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        std::cerr << "Renderer not created: " << SDL_GetError() << std::endl;

        return false;
    }
    
    set_clear_color(clear_color_r, clear_color_g, clear_color_b, clear_color_a);

    status = RUNNING;
    
    return true;
}


void Game::handle_events()
{
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                status = INACTIVE;
                break;
            default:
                break;
        }
    }

    return;
}


void Game::update()
{
}


void Game::render()
{
    clear_screen();
    SDL_RenderPresent(renderer);

    return;
}


void Game::clean()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return;
}


inline void Game::clear_screen()
{
    SDL_SetRenderDrawColor(renderer, clear_color.r, clear_color.g,
                           clear_color.b, clear_color.a);
    SDL_RenderClear(renderer);

    return;
}


inline void Game::set_clear_color(const int & clear_color_r,
                                  const int & clear_color_g,
                                  const int & clear_color_b,
                                  const int & clear_color_a)
{
    clear_color.r = clear_color_r;
    clear_color.g = clear_color_g;
    clear_color.b = clear_color_b;
    clear_color.a = clear_color_a;
    
    return;
}
