// File: Game.cpp
// Author: Ujjwal Jung Pandey
// Description: Implementation of game controller.


#include <iostream>


#include "Game.h"


bool Game::init(int lib_flags,
                std::string title,
                int win_x,
                int win_y,
                int win_w,
                int win_h,
                int win_flags,
                int clear_color_r,
                int clear_color_g,
                int clear_color_b,
                int clear_color_a)
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

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        std::cerr << "Renderer not created: " << SDL_GetError() << std::endl;

        return false;
    }
    
    clear_color.r = clear_color_r;
    clear_color.g = clear_color_g;
    clear_color.b = clear_color_b;
    clear_color.a = clear_color_a;

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


void Game::clear_screen()
{
    SDL_SetRenderDrawColor(renderer, clear_color.r, clear_color.g,
                           clear_color.b, clear_color.a);
    SDL_RenderClear(renderer);

    return;
}


void Game::set_clear_color(int clear_color_r,
                           int clear_color_g,
                           int clear_color_b,
                           int clear_color_a)
{
    clear_color.r = clear_color_r;
    clear_color.g = clear_color_g;
    clear_color.b = clear_color_b;
    clear_color.a = clear_color_a;
    
    return;
}
    

int main()
{
    Game * TheGame = new Game();
    TheGame -> init();
    
    while(TheGame -> get_status() != INACTIVE)
    {
        TheGame -> handle_events();
        TheGame -> update();
        TheGame -> render();
    }
    TheGame -> clean();

    return 0;
}

    
