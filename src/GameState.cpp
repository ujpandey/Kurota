#include "GameState.h"


//-----------------------------------------------------------------------------
// GameState
//-----------------------------------------------------------------------------
GameState::GameState(const std::string & id)
    : _id(id)
{}

GameState::~GameState()
{}

// void GameState::handle_event()
// {
// }

void GameState::update()
{
    for (std::vector< GameObject * >::iterator it = game_objects.begin();
         it != game_objects.end(); ++it)
    {
        (*it) -> update();
    }
    SDL_Delay(30);
}

void GameState::draw()
{
    for (std::vector< GameObject * >::iterator it = game_objects.begin();
         it != game_objects.end(); ++it)
    {
        (*it) -> draw(renderer);
    }
}

const std::string & GameState::get_id()
{
    return _id;
}

void GameState::on_entry()
{
    // Make resources persistent and switch.
}

void GameState::on_exit()
{
    // Temporary solution to clear things out like this. Want Persistence.
    TextureManager::get_instance() -> clear();
    EventHandler::get_instance() -> clear();
    for (std::vector< GameObject * >::iterator it = game_objects.begin();
         it != game_objects.end(); ++it)
    {
        delete (*it);
    }
}

void GameState::register_game_object(GameObject * g_o)
{
    game_objects.push_back(g_o);
    g_o -> set_successor(this);
    EventManager::get_instance() -> lease(g_o);
}

void GameState::release_game_object(GameObject * g_o)
{
    std::vector< GameObject * >::iterator it =
        std::find(game_objects.begin(), game_objects.end(), g_o);
    if (it != game_objects.end())
        game_objects.erase(it);
    EventManager::get_instance() -> release(g_o);
}


//-----------------------------------------------------------------------------
// SplashScreen
//-----------------------------------------------------------------------------
SplashScreen::SplashScreen(const std::string & id)
    : GameState(id)
{}


//-----------------------------------------------------------------------------
// PlayState
//-----------------------------------------------------------------------------
PlayState::PlayState(const std::string & id)
    : GameState(id)
{}


//-----------------------------------------------------------------------------
// GameStateManager
//-----------------------------------------------------------------------------
GameStateManager::GameStateManager()
{}

GameStateManager::~GameStateManager()
{}

void GameStateManager::update()
{
    (*(_game_states.end() - 1)) -> update();
}

void GameStateManager::draw()
{
    (*(_game_states.end() - 1)) -> update();
}

const std::string & GameStateManager::get_current_state_id()
{
    return (*(_game_states.end() - 1)) -> get_id();
}

void GameStateManager::register_game_object(GameObject * g_o)
{
    (*(_game_states.end() - 1)) -> register_game_object();
}

void GameStateManager::release_game_object(GameObject * g_o)
{
    (*(_game_states.end() - 1)) -> release_game_object();
}

void GameStateManager::change(GameState * state)
{
    pop();
    push(state);
}

void GameStateManager::push(GameState * state)
{
    state -> on_entry();
    _game_states.push_back(state);
}

void GameStateManager::pop()
{
    (*(_game_states.end() - 1)) -> on_exit();
    _game_states.pop_back(); 
}
