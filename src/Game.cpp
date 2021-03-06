// File: Game.cpp
// Author: Ujjwal Jung Pandey
// Description: Implementation of game controller.


#include "Game.h"
#include "EventManager.h"
#include "TextureManager.h"
#include "GameState.h"


Game * Game::instance = NULL;


Game::Game()
    : EventHandler("Game"), _running(true)
{
}


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

    if (TTF_Init() == -1)
    {
        std::cerr << "SDL_ttf initiation failed: "
                  << TTF_GetError() << std::endl;
        
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        std::cerr << "Renderer not created: " << SDL_GetError() << std::endl;

        return false;
    }
    
    set_clear_color(clear_color_r, clear_color_g, clear_color_b, clear_color_a);

    font = TTF_OpenFont("../assets/arial.ttf", 24);
    if (font == NULL)
    {
        std::cerr << "Font not loaded: " << TTF_GetError() << std::endl;

        return false;
    }

    SDL_StartTextInput();

//     _fps = 60;
//     _ticks_per_frame = 1000 / _fps;

//     _timer.start();
//     _ticks = 0;
//  GameStateManager::get_instance() -> push(new PlayState);
    GameStateManager::get_instance() -> push(new SplashScreen);
    
    return true;
}


void Game::on_quit()
{
    _running = false;
}


void Game::handle_event()
{
    EventManager::get_instance() -> handle_event();
}


void Game::update()
{
    GameStateManager::get_instance() -> update();
    SDL_Delay(30);
}


void Game::draw()
{
    clear_screen();

    GameStateManager::get_instance() -> draw(renderer);
    
    SDL_RenderPresent(renderer);
//     Uint32 _ticks_left = _timer.get_ticks() - _ticks;
//     if (_ticks_left < _ticks_per_frame)
//     {
//         SDL_Delay(_ticks_per_frame - _ticks_left);
//     }
//     _ticks = _timer.get_ticks();

    return;
}


void Game::clean()
{
    TextureManager::get_instance() -> clear();
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
    GameStateManager::get_instance() -> register_game_object(g_o);
}


void Game::release_game_object(GameObject * g_o)
{
    GameStateManager::get_instance() -> release_game_object(g_o);
}

const bool Game::running() const
{
    return _running;
}


SDL_Renderer * Game::get_renderer() const
{
    return renderer;
}

TTF_Font * Game::get_font() const
{
    return font;
}
