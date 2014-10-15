// File: Game.cpp
// Author: Ujjwal Jung Pandey
// Description: Implementation of game controller.


#include "Game.h"


Game * Game::instance = NULL;


Game * Game::get_instance()
{
    if (instance)
        return instance;
    instance = new Game;
    return instance;
}


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
    for (std::vector< GameObject * >::iterator it = game_objects.begin();
         it != game_objects.end(); ++it)
    {
        (*it) -> update();
    }
    SDL_Delay(300);
}


void Game::render()
{
    clear_screen();

    for (std::vector< GameObject * >::iterator it = game_objects.begin();
         it != game_objects.end(); ++it)
    {
        (*it) -> draw(renderer);
    }
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


void Game::set_clear_color(const int & clear_color_r,
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


void Game::register_game_object(GameObject * g_o)
{
    game_objects.push_back(g_o);
}


void Game::release_game_object(GameObject * g_o)
{
    std::vector< GameObject * >::iterator it =
        std::find(game_objects.begin(), game_objects.end(), g_o);
    if (it != game_objects.end())
        game_objects.erase(it);
}


const GameStatus & Game::get_status() const
{
    return status;
}


void Game::set_status(const GameStatus & s)
{
    status = s;
}


SDL_Renderer * Game::get_renderer() const
{
    return renderer;
}
