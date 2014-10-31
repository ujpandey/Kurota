// File: Game.h
// Author: Ujjwal Jung Pandey
// Description: Abstraction of the core game controls.


#ifndef GAME_H
#define GAME_H


#include "Includes.h"
#include "EventManager.h"
#include "GameObject.h"
#include "TextureManager.h"


class GameObject;


SDL_FORCE_INLINE SDL_bool SDL_PointInRect(const SDL_Point *p, const SDL_Rect *r)
{
    return ( (p->x >= r->x) && (p->x < (r->x + r->w)) &&
             (p->y >= r->y) && (p->y < (r->y + r->h)) ) ? SDL_TRUE : SDL_FALSE;
}


enum GameStatus {RUNNING, PAUSED, INACTIVE};


enum Direction {NORTH, EAST, WEST, SOUTH};


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
              const int & win_flags=SDL_WINDOW_RESIZABLE,
              const int & clear_color_r=255,
              const int & clear_color_g=255,
              const int & clear_color_b=255,
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

    const GameStatus & get_status() const;
    void set_status(const GameStatus & status);
    SDL_Renderer * get_renderer() const;
    TTF_Font * get_font() const;

protected:
    Game();
    
private:
    GameStatus status;
    SDL_Color clear_color;
    SDL_Window * window;
    SDL_Renderer * renderer;
    TTF_Font * font;

    std::vector< GameObject * > game_objects;
    static Game * instance;
};


#endif
