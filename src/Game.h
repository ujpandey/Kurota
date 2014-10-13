// File: Game.h
// Author: Ujjwal Jung Pandey
// Description: Abstraction of the core game controls.


#ifndef GAME_H
#define GAME_H


#include <algorithm>
#include <iostream>
#include <vector>


#include "SDL.h"
#include "SDL_image.h"


#include "GameObject.h"


class GameObject;


enum GameStatus {RUNNING, PAUSED, INACTIVE};


class Game
{
public:
    static Game * get_instance();

    bool init(const int & lib_flags=SDL_INIT_VIDEO,
              const std::string & title="Kurota!",
              const int & win_x=SDL_WINDOWPOS_CENTERED,
              const int & win_y=SDL_WINDOWPOS_CENTERED,
              const int & win_w=800,
              const int & win_h=600,
              const int & win_flags=SDL_WINDOW_RESIZABLE,
              const int & clear_color_r=255,
              const int & clear_color_g=255,
              const int & clear_color_b=255,
              const int & clear_color_a=255);
    void handle_events();
    void update();
    void render();
    void clean();
    void clear_screen();
    void set_clear_color(const int & clear_color_r=255,
                         const int & clear_color_g=255,
                         const int & clear_color_b=255,
                         const int & clear_color_a=255);
    void register_game_object(GameObject * g_o);
    void release_game_object(GameObject * g_o);
    const GameStatus & get_status() const;
    void set_status(const GameStatus & status);
    SDL_Renderer * get_renderer() const;

protected:
    Game(){}
    
private:
    GameStatus status;
    SDL_Color clear_color;
    SDL_Window * window;
    SDL_Renderer * renderer;
    SDL_Event event;
    
    std::vector< GameObject * > game_objects;
    static Game * instance;
};


#endif
