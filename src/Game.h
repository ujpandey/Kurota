// File: Game.h
// Author: Ujjwal Jung Pandey
// Description: Abstraction of the core game controls.


#ifndef GAME_H
#define GAME_H


#include "SDL.h"


enum GameStatus {RUNNING, PAUSED, INACTIVE};


class Game
{
public:
    Game(){}
    ~Game(){}

    bool init(int lib_flags=SDL_INIT_VIDEO,
              std::string title="Kurota!",
              int win_x=SDL_WINDOWPOS_CENTERED,
              int win_y=SDL_WINDOWPOS_CENTERED,
              int win_w=800,
              int win_h=600,
              int win_flags=SDL_WINDOW_RESIZABLE,
              int clear_color_r=255,
              int clear_color_g=255,
              int clear_color_b=255,
              int clear_color_a=255);
    void handle_events();
    void update();
    void render();
    void clean();
    void clear_screen();
    void set_clear_color(int clear_color_r=255,
                         int clear_color_g=255,
                         int clear_color_b=255,
                         int clear_color_a=255);

    const GameStatus & get_status() const { return status; }
    
private:
    GameStatus status;
    SDL_Color clear_color;
    SDL_Window * window;
    SDL_Renderer * renderer;
    SDL_Event event;
};


#endif