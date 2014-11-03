#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Includes.h"
#include "GameObject.h"

class GameObject;

class GameState : public EventHandler
{
public:
    virtual ~GameState();
    //virtual void handle_event();
    virtual void update();
    virtual void draw(SDL_Renderer * renderer);
    virtual const std::string & get_id();

    virtual void on_entry();
    virtual void on_exit();
    
    void register_game_object(GameObject * g_o);
    void release_game_object(GameObject * g_o);
    
protected:
    GameState(const std::string & id);
    
private:
    std::vector< GameObject * > game_objects;
};

class SplashScreen : public GameState
{
public:
    SplashScreen(const std::string & id="Splash");

    virtual void on_entry();
};

class PlayState : public GameState
{
public:
    PlayState(const std::string & id="Play");

    virtual void on_entry();
};

class GameStateManager
{
public:
    static GameStateManager * get_instance();
    virtual ~GameStateManager();
    //virtual void handle_event();
    virtual void update();
    virtual void draw(SDL_Renderer * renderer);
    virtual const std::string & get_current_state_id();

    void register_game_object(GameObject * g_o);
    void release_game_object(GameObject * g_o);

    void change(GameState * state);
    void push(GameState * state);
    void pop();
    
protected:
    GameStateManager();

private:
    static GameStateManager * _instance;
    std::vector< GameState * > _game_states;
};

#endif
