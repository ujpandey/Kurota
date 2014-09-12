/******************************************************************************
 * main.cpp: Kurota main entry point.
 *
 * Latest Change on 09/12/2014 by Ujjwal
 * - Introduce the main game framework in the form of Game & GameObject classes.
 *
 * Latest Change on 09/11/2014 by Ujjwal
 * - Initiate project. Create a SDL window and do some basic tests.
 * 
 * Current status:
 * - Only a basic SDL demo for now.
 *
 * TODO:
 * - Add an animation class.
 ******************************************************************************/



#include <iostream>
#include <string>


#include "SDL.h"
#include "SDL_image.h"


int main()
{
    // SDL initiation
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "Failure to initialize video: "
                  << SDL_GetError() << std::endl;
        
        return -1;
    }
    
    std::string main_title = "Kurota!";
    int WIN_X = 200, WIN_Y = 200, WIN_W = 640, WIN_H = 480;
    SDL_Window * main_window;
    main_window = SDL_CreateWindow(main_title.c_str(),
                                   WIN_X, WIN_Y, WIN_W, WIN_H,
                                   SDL_WINDOW_RESIZABLE);
    
    if (main_window == NULL)
    {
        std::cerr << "Creating the main window failed: "
                  << SDL_GetError() << std::endl;
        
        return -2;
    }

    // SDL_image initiation
    int IMG_flags = IMG_INIT_PNG | IMG_INIT_JPG;
    int IMG_init_code = IMG_Init(IMG_flags);

    if (IMG_init_code & IMG_flags != IMG_flags)
    {
        std::cerr << "SDL_image initiation failed: "
                  << IMG_GetError() << std::endl;

        return -3;
    }

    SDL_Renderer * main_renderer;
    main_renderer = SDL_CreateRenderer(main_window, -1,
                                       SDL_RENDERER_ACCELERATED);

    SDL_Surface * player_surface;
    player_surface = IMG_Load("spritesheet_env.jpg");
    if (!player_surface)
    {
        std::cerr << "Failure opening file: "
                  << IMG_GetError() << std::endl;

        return -4;
    }

    SDL_Texture * player_texture;
    player_texture = SDL_CreateTextureFromSurface(main_renderer, player_surface);
    SDL_FreeSurface(player_surface);
    
    SDL_Rect bg_rect;

    SDL_Event event;

    int i = 0, j = 0;

    bool game_running = true;

    while(game_running)
    {
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT)
            {
                std::cout << "Got a quit";

                game_running = false;
            }
        }

        SDL_SetRenderDrawColor(main_renderer, 0, 0, 255, 255);
        
        SDL_RenderClear(main_renderer);
        
        SDL_SetRenderDrawColor(main_renderer, 255, 0, 0, 255);
        
        bg_rect.x = 50 + i;
        bg_rect.y = 50 + j;
        bg_rect.w = 100;
        bg_rect.h = 100;
        
        SDL_RenderFillRect(main_renderer, &bg_rect);

        SDL_RenderCopy(main_renderer, player_texture, NULL, NULL);

        SDL_RenderPresent(main_renderer);
    }

    SDL_DestroyTexture(player_texture);
    SDL_DestroyRenderer(main_renderer);
    SDL_DestroyWindow(main_window);

    IMG_Quit();
    SDL_Quit();

    
    
}
