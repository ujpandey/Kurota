// File: Game.h
// Author: Ujjwal Jung Pandey
// Description: Abstraction of the core game controls.


#ifndef GAME_H
#define GAME_H


#include "Includes.h"
#include "EventHandler.h"
//#include "Timer.h"


class GameObject;


class Game : public EventHandler
{
public:
    static Game * get_instance();

    bool init(const int & lib_flags=SDL_INIT_VIDEO,
              const std::string & title="Kurota!",
              const int & win_x=SDL_WINDOWPOS_CENTERED,
              const int & win_y=SDL_WINDOWPOS_CENTERED,
              const int & win_w=1024,
              const int & win_h=768,
              const int & win_flags=SDL_WINDOW_SHOWN,
              const int & clear_color_r=0,
              const int & clear_color_g=0,
              const int & clear_color_b=0,
              const int & clear_color_a=255);

    void on_quit();
    void handle_event();
    void update();
    void draw();
    void clean();
    void clear_screen();
    void set_clear_color(const int & clear_color_r=255,
                         const int & clear_color_g=255,
                         const int & clear_color_b=255,
                         const int & clear_color_a=255);

    void register_game_object(GameObject * g_o);
    void release_game_object(GameObject * g_o);

    const bool running() const;
    SDL_Renderer * get_renderer() const;
    TTF_Font * get_font() const;

    const SDL_Rect * get_map_bounds() const;

protected:
    Game();
    
private:
    bool _running;
    SDL_Color clear_color;
    SDL_Rect _map;
//     int _fps;
//     int _ticks_per_frame;
//     Timer _timer;
//     Uint32 _ticks;
// Map map;
    SDL_Window * window;
    SDL_Renderer * renderer;
    TTF_Font * font;
    static Game * instance;
};


#endif
